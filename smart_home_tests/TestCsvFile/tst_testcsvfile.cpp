#include <QtTest>

#include "csvfile.h"
#include <sstream>
#include <string>

using data::CsvFile;

// DANGER: do not auto-format this file. We use raw strings R": .... :" to
// contain CSV text content for the tests which have one row per line.
// Auto-formatting may indent subsequent lines and cause tests to fail.

/// CsvFile tests: Do NOT modify! (except in the following suggestion)
/// It is recommended that you perform the following:
/// - Comment out all but the first test.
/// - Once the first test passes, activate the second while leaving the first
///   test active.
/// - Once the second test passes, move to the third test, etc.
/// Doing it this way will incrementally build up the functionality of your
/// CsvFile class in a test-driven style, while ensuring all of the previous
/// tests still pass as you make changes to your implementation.
/// Commenting out the later tests is just to prevent any compilation errors
/// from occuring (due to unimplemented aspects) that may otherwise prevent
/// you from testing earlier aspects.
class TestCsvFile : public QObject
{
  Q_OBJECT

public:
  TestCsvFile();
  ~TestCsvFile();

private slots:
  void initTestCase();
  void cleanupTestCase();
  void test_loadFailureForEmptyCsvFile();
  void test_loadSuccessForHeaderButNoDataCsvFile();
  void test_outOfRangeReturnsEmptyString();
  void test_headerFieldsCorrectlyRead();
  void test_commaSeparatedRowDataAccessible();
  void test_multipleRowsOfData();
  void test_emptyFieldAtEndOfLine();
  void test_loadFailureOnRowWithDifferingNumberOfColumns();
  void test_preservationOfWhitespaceInFields();
  void test_lineEndingOnLastLine();
  void test_doubleQuotedFields();
  void test_doubleQuotedFieldsMixedWithUnquoted();
  void test_replacementOfBlackslashNInQuotedFieldsWithNewline();
  void test_doubleQuotesWithinFields();

private:
  unsigned int _failureCount;    ///< count of all failures that have occurred
  unsigned int _assertionCount;  ///< tally of the number of assertions made
};

// Using a macro to ensure the QVERIFY2 has the correct location in the source file
// Otherwise these tests are not very useful.
#define equal(expected, actual, failMessage) \
  ++_assertionCount; \
  if (not (expected == actual)) ++_failureCount; \
  QVERIFY2(expected == actual, failMessage);

TestCsvFile::TestCsvFile() : _failureCount{0}, _assertionCount{0}
{

}

TestCsvFile::~TestCsvFile()
{

}

void TestCsvFile::initTestCase()
{
  _assertionCount = 0;
  _failureCount = 0;
}

void TestCsvFile::cleanupTestCase()
{
  // Marking version will calculate the Mark here.
  qDebug() << "This is not the marking file, assertions passed: "
           << (_assertionCount - _failureCount)
           << " / " << _assertionCount;
}

void TestCsvFile::test_loadFailureForEmptyCsvFile()
{
  std::stringstream data{""};
  CsvFile csvFile{data};

  equal(-1, csvFile.numberOfRows(), "numberOfRows() must indicate load failure for empty input data");
  equal(-1, csvFile.numberOfColumns(), "numberOfColumns() must indicate load failure for empty input data");
  equal(std::string{""}, csvFile.at(1, 1), "at(int,int) must return empty string for empty input data");
  equal(std::string{""}, csvFile.headerAt(1), "headerAt(int) must return empty string for empty input data");
  equal(-1, csvFile.columnIndexOf("Name"), "columnIndexOf(string) must return -1 for empty input data");
}

void TestCsvFile::test_loadSuccessForHeaderButNoDataCsvFile()
{
  std::stringstream data{"Header"};
  CsvFile csvFile{data};

  equal(0, csvFile.numberOfRows(), "numberOfRows() must indicate the number of rows in the data for successful load");
  equal(1, csvFile.numberOfColumns(), "numberOfColumns() must indicate the number of columns for successful load");
  equal(std::string{""}, csvFile.at(1, 1), "at(int,int) must return empty string for empty no rows (out of range)");
  equal(std::string{"Header"}, csvFile.headerAt(1), "headerAt(int) must return the column name for successful load");
  equal(1, csvFile.columnIndexOf("Header"), "columnIndexOf(string) must return index for for successful load");
}

void TestCsvFile::test_outOfRangeReturnsEmptyString()
{
  std::stringstream data{R":(Header1,Header2
Cell 1,Cell 2
):"};
  CsvFile csvFile{data};

  equal(std::string{""}, csvFile.headerAt(3), "headerAt() must return empty string when index out of range");
  equal(std::string{""}, csvFile.headerAt(0), "headerAt() must return empty string when index out of range (zero is out of range)");
  equal(std::string{""}, csvFile.at(2,1), "at() must return empty string when row index out of range");
  equal(std::string{""}, csvFile.at(0,1), "at() must return empty string when row index out of range (zero is out of range)");
  equal(std::string{""}, csvFile.at(1,3), "at() must return empty string when column index out of range");
  equal(std::string{""}, csvFile.at(1,0), "at() must return empty string when column index out of range (zero is out of range)");
}

void TestCsvFile::test_headerFieldsCorrectlyRead()
{
  std::stringstream data{R":(Header1,Header2,Header3):"};
  CsvFile csvFile{data};

  equal(0, csvFile.numberOfRows(), "numberOfRows() must indicate zero, as only the header is present");
  equal(3, csvFile.numberOfColumns(), "numberOfColumns() must indicate 3 columns for the three header fields");
  equal(std::string{"Header1"}, csvFile.headerAt(1), "headerAt(1) must return the first header field");
  equal(std::string{"Header2"}, csvFile.headerAt(2), "headerAt(2) must return the second header field");
  equal(std::string{"Header3"}, csvFile.headerAt(3), "headerAt(3) must return the third header field");
}

void TestCsvFile::test_commaSeparatedRowDataAccessible()
{
  std::stringstream data{R":(Header1,Header2,Header3
Field1,Field2,Field3):"};
  CsvFile csvFile{data};

  equal(1, csvFile.numberOfRows(), "numberOfRows() must indicate 1, as the header + 1 row is present");
  equal(3, csvFile.numberOfColumns(), "numberOfColumns() must indicate 3 columns for the three fields");
  equal(std::string{"Field1"}, csvFile.at(1,1), "at(1,1) must return the first field of the first row");
  equal(std::string{"Field2"}, csvFile.at(1,2), "at(1,2) must return the second field of the first row");
  equal(std::string{"Field3"}, csvFile.at(1,3), "at(1,3) must return the third field of the first row");
}

void TestCsvFile::test_multipleRowsOfData()
{
  std::stringstream data{R":(Header1,Header2,Header3
Row1Field1,Row1Field2,Row1Field3
Row2Field1,Row2Field2,Row2Field3
Row3Field1,Row3Field2,Row3Field3):"};
  CsvFile csvFile{data};

  equal(3, csvFile.numberOfRows(), "numberOfRows() must indicate 3, as the header + 3 rows are present");
  equal(3, csvFile.numberOfColumns(), "numberOfColumns() must indicate 3 columns for the three fields");

  equal(std::string{"Row1Field1"}, csvFile.at(1,1), "at(1,1) must return the first field of the first row");
  equal(std::string{"Row1Field2"}, csvFile.at(1,2), "at(1,2) must return the second field of the first row");
  equal(std::string{"Row1Field3"}, csvFile.at(1,3), "at(1,3) must return the third field of the first row");

  equal(std::string{"Row2Field1"}, csvFile.at(2,1), "at(2,1) must return the first field of the second row");
  equal(std::string{"Row2Field2"}, csvFile.at(2,2), "at(2,2) must return the second field of the second row");
  equal(std::string{"Row2Field3"}, csvFile.at(2,3), "at(2,3) must return the third field of the second row");

  equal(std::string{"Row3Field1"}, csvFile.at(3,1), "at(3,1) must return the first field of the third row");
  equal(std::string{"Row3Field2"}, csvFile.at(3,2), "at(3,2) must return the second field of the third row");
  equal(std::string{"Row3Field3"}, csvFile.at(3,3), "at(3,3) must return the third field of the third row");
}

void TestCsvFile::test_emptyFieldAtEndOfLine()
{
  std::stringstream dataEmptyFieldAtEnd{R":(Header1,Header2,Header3
Field1,Field2,):"};
  CsvFile csvFile{dataEmptyFieldAtEnd};

  equal(1, csvFile.numberOfRows(), "numberOfRows() must indicate 1, as the header + 1 row is present");
  equal(3, csvFile.numberOfColumns(), "numberOfColumns() must indicate 3 columns for the three fields");

  equal(std::string{"Field1"}, csvFile.at(1,1), "at(1,1) must return the first field of the first row");
  equal(std::string{"Field2"}, csvFile.at(1,2), "at(1,2) must return the second field of the first row");
  equal(std::string{""}, csvFile.at(1,3), "at(1,3) must return the third (empty string) field of the first row");
}

void TestCsvFile::test_loadFailureOnRowWithDifferingNumberOfColumns()
{
  std::stringstream dataExtraColumnInRow{R":(Header1,Header2
Field1,Field2,Field3Error):"};
  CsvFile csvFile{dataExtraColumnInRow};

  equal(-1, csvFile.numberOfRows(), "numberOfRows() must indicate load failure for row with extra column");
  equal(-1, csvFile.numberOfColumns(), "numberOfColumns() must indicate load failure for row with extra column");

  std::stringstream dataMissingColumnInRow{R":(Header1,Header2
Field1):"};
  csvFile = CsvFile{dataMissingColumnInRow};

  equal(-1, csvFile.numberOfRows(), "numberOfRows() must indicate load failure for row with missing column");
  equal(-1, csvFile.numberOfColumns(), "numberOfColumns() must indicate load failure for row with missing column");
}

void TestCsvFile::test_preservationOfWhitespaceInFields()
{
  std::stringstream data{"  Header1,  Header2,Header3  ,Header  4,  Header  5  ,Header6  \n"
"  Field1,  Field2,Field3  ,Field  4,  Field  5  ,Field6  "};
  CsvFile csvFile{data};

  equal(1, csvFile.numberOfRows(), "numberOfRows() must be 1 for whitespace test");
  equal(6, csvFile.numberOfColumns(), "numberOfColumns() must be 6 for whitespace test");

  equal(std::string{"  Header1"}, csvFile.headerAt(1), "headerAt(1) must preserve whitespace at line beginning");
  equal(std::string{"  Header2"}, csvFile.headerAt(2), "headerAt(2) must preserve whitespace after comma");
  equal(std::string{"Header3  "}, csvFile.headerAt(3), "headerAt(3) must preserve whitespace before comma");
  equal(std::string{"Header  4"}, csvFile.headerAt(4), "headerAt(4) must preserve internal whitespace");
  equal(std::string{"  Header  5  "}, csvFile.headerAt(5), "headerAt(5) must preserve all whitespace");
  equal(std::string{"Header6  "}, csvFile.headerAt(6), "headerAt(6) must preserve whitespace at line end");

  equal(std::string{"  Field1"}, csvFile.at(1,1), "at(1, 1) must preserve whitespace at line beginning");
  equal(std::string{"  Field2"}, csvFile.at(1,2), "at(1, 2) must preserve whitespace after comma");
  equal(std::string{"Field3  "}, csvFile.at(1, 3), "at(1, 3) must preserve whitespace before comma");
  equal(std::string{"Field  4"}, csvFile.at(1, 4), "at(1, 4) must preserve internal whitespace");
  equal(std::string{"  Field  5  "}, csvFile.at(1, 5), "at(1, 5) must preserve all whitespace");
  equal(std::string{"Field6  "}, csvFile.at(1,6), "at(1, 6) must preserve whitespace at line end");
}

void TestCsvFile::test_lineEndingOnLastLine()
{
  std::stringstream data{R":(Header1
Field1):"};
  CsvFile csvFile{data};

  equal(1, csvFile.numberOfRows(), "numberOfRows() must be 1 for line ending test, without extra CRLF");
  equal(1, csvFile.numberOfColumns(), "numberOfColumns() must be 1 for line ending test, without extra CRLF");

  data = std::stringstream{R":(Header1
Field1
):"};
  csvFile = CsvFile{data};

  equal(1, csvFile.numberOfRows(), "numberOfRows() must be 1 for line ending test, WITH extra CRLF");
  equal(1, csvFile.numberOfColumns(), "numberOfColumns() must be 1 for line ending test, WITH extra CRLF");
}

void TestCsvFile::test_doubleQuotedFields()
{
  std::stringstream data{R":("Header,1","Header,2","Header,3","  Header  4  "
"Field,1","Field,2","Field,3","  Field  4  "):"};
  CsvFile csvFile{data};

  equal(1, csvFile.numberOfRows(), "numberOfRows() must indicate 1, as the header + 1 row is present (double quote test)");
  equal(4, csvFile.numberOfColumns(), "numberOfColumns() must indicate 4 columns for the four fields (double quote test)");

  equal(std::string{"Header,1"}, csvFile.headerAt(1), "headerAt(1) must return the first header without quotes");
  equal(std::string{"Header,2"}, csvFile.headerAt(2), "headerAt(2) must return the second header without quotes");
  equal(std::string{"Header,3"}, csvFile.headerAt(3), "headerAt(3) must return the third header without quotes");
  equal(std::string{"  Header  4  "}, csvFile.headerAt(4), "headerAt(4) must return the fourth header without quotes, preserving whitespace");

  equal(std::string{"Field,1"}, csvFile.at(1,1), "at(1,1) must return the first field without quotes");
  equal(std::string{"Field,2"}, csvFile.at(1,2), "at(1,2) must return the second field without quotes");
  equal(std::string{"Field,3"}, csvFile.at(1,3), "at(1,3) must return the third field without quotes");
  equal(std::string{"  Field  4  "}, csvFile.at(1,4), "at(1,4) must return the fourth field without quotes, preserving whitespace");

  data = std::stringstream{R":( "Header1"
  "Field1"):"};
  csvFile = CsvFile{data};

  equal(-1, csvFile.numberOfRows(), "numberOfRows() must indicate load failure for whitespace outside double quotes (before quote)");
  equal(-1, csvFile.numberOfColumns(), "numberOfColumns() must indicate load failure for whitespace outside double quotes (before quote)");

  data = std::stringstream{R":("Header1"  ,Header2
"Field1"  ,Field2):"};
  csvFile = CsvFile{data};

  equal(-1, csvFile.numberOfRows(), "numberOfRows() must indicate load failure for whitespace outside double quotes (after quote)");
  equal(-1, csvFile.numberOfColumns(), "numberOfColumns() must indicate load failure for whitespace outside double quotes (after quote)");
}

void TestCsvFile::test_doubleQuotedFieldsMixedWithUnquoted()
{
  std::stringstream data{R":("Header,1",Header2,"Header,3",Header4
"Field,1",Field2,"Field,3",Field4):"};
  CsvFile csvFile{data};

  equal(1, csvFile.numberOfRows(), "numberOfRows() must indicate 1, as the header + 1 row is present (mixed test)");
  equal(4, csvFile.numberOfColumns(), "numberOfColumns() must indicate 4 columns for the three fields (mixed test)");

  equal(std::string{"Header,1"}, csvFile.headerAt(1), "headerAt(1) must return the first header without quotes (mixed test)");
  equal(std::string{"Header2"}, csvFile.headerAt(2), "headerAt(2) must return the second header without quotes (mixed test)");
  equal(std::string{"Header,3"}, csvFile.headerAt(3), "headerAt(3) must return the third header without quotes (mixed test)");
  equal(std::string{"Header4"}, csvFile.headerAt(4), "headerAt(4) must return the fourth header without quotes (mixed test)");

  equal(std::string{"Field,1"}, csvFile.at(1,1), "at(1,1) must return the first field without quotes (mixed test)");
  equal(std::string{"Field2"}, csvFile.at(1,2), "at(1,2) must return the second field without quotes (mixed test)");
  equal(std::string{"Field,3"}, csvFile.at(1,3), "at(1,3) must return the third field without quotes (mixed test)");
  equal(std::string{"Field4"}, csvFile.at(1,4), "at(1,4) must return the fourth field without quotes (mixed test)");
}

void TestCsvFile::test_replacementOfBlackslashNInQuotedFieldsWithNewline()
{
  std::stringstream data{R":("Header\n1","He\nader\n2",Header\n3
"Field\n1","Fi\neld\n2",Field\n3):"};
  CsvFile csvFile{data};

  equal(std::string{"Header\n1"}, csvFile.headerAt(1), "headerAt(1) must return the first header with '\\n' replaced with newline");
  equal(std::string{"He\nader\n2"}, csvFile.headerAt(2), "headerAt(2) must return the second header with '\\n' replaced with newline");
  equal(std::string{"Header\\n3"}, csvFile.headerAt(3), "headerAt(3) must return the thord header WITHOUT '\\n' replaced with newline, since it is unquoted");

  equal(std::string{"Field\n1"}, csvFile.at(1,1), "at(1,1) must return the first field with '\\n' replaced with newline");
  equal(std::string{"Fi\neld\n2"}, csvFile.at(1,2), "at(1,2) must return the second field with '\\n' replaced with newline");
  equal(std::string{"Field\\n3"}, csvFile.at(1,3), "at(1,3) must return the third field WITHOUT '\\n' replaced with newline, since it is unquoted");
}

void TestCsvFile::test_doubleQuotesWithinFields()
{
  std::stringstream data{R":("Header""1"
"Field""1"):"};
  CsvFile csvFile{data};

  equal(1, csvFile.numberOfRows(), "numberOfRows() must indicate 1, as the header + 1 row is present (double quote test)");
  equal(1, csvFile.numberOfColumns(), "numberOfColumns() must indicate 4 columns for the three fields (double quote test)");

  equal(std::string{"Header\"1"}, csvFile.headerAt(1), "headerAt(1) must return the first header with internal quotes maintained, no outer quotes");
  equal(std::string{"Field\"1"}, csvFile.at(1,1), "at(1,1) must return the first field with internal quotes maintained, no outer quotes");

  data = std::stringstream{R":("Header"",""1"
"Field"",""1"):"};
  csvFile = CsvFile{data};

  equal(1, csvFile.numberOfRows(), "numberOfRows() must indicate 1, as the header + 1 row is present (double quote test with comma)");
  equal(1, csvFile.numberOfColumns(), "numberOfColumns() must indicate 4 columns for the three fields (double quote test with comma)");

  equal(std::string{"Header\",\"1"}, csvFile.headerAt(1), "headerAt(1) must return the first header with internal quotes maintained, no outer quotes, and internal commas preserved");
  equal(std::string{"Field\",\"1"}, csvFile.at(1,1), "at(1,1) must return the first field with internal quotes maintained, no outer quotes, and internal commas preserved");
}

QTEST_APPLESS_MAIN(TestCsvFile)

#include "tst_testcsvfile.moc"
