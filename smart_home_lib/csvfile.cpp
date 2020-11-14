#include "csvfile.h"

using namespace data;

CsvFile::CsvFile(std::istream &input)
{
  // TODO: implement the constructor
    std::string entryData{};
    if (!input.fail()){
        std::getline(input,entryData);
        CSVData.push_back(entryData);
    }
    else {
        CSVData.clear();
    }
}

int CsvFile::numberOfColumns() const
{
  // TODO: implement this method. See header for description.

    if (!CSVData.empty()){
        int columns{0};
        for (int i = 0; i < (int)CSVData[0].size(); ++i){
            if (CSVData[0][i] == ','){
                columns++;
            }
        }
        return  columns + 1;
    }
    else {
        return -1;
    }
}

int CsvFile::numberOfRows() const
{
  // TODO: implement this method. See header for description.
    if (!CSVData.empty()){
        return  CSVData.size();
    }
    else {
        return -1;
    }

}

std::string CsvFile::at(int row, int column) const
{
  // TODO: implement this method. See header for description.


    if (!CSVData.empty()){
        std::size_t previousFound{};
        std::size_t currentFound = CSVData[row-1].find(",");

        if (column == 1){
            return CSVData[row - 1].substr(0,currentFound);
        }
        else if (column == numberOfColumns()) {
            for (int i = 1; i < column -1; ++i){
                previousFound = currentFound;
                currentFound = CSVData[row -1].find(",", previousFound+1);
            }
            return CSVData[row - 1].substr(currentFound+1, CSVData[row - 1].length()-currentFound);
        }
        else {
            for (int i = 1; i < column; ++i){
                previousFound = currentFound;
                currentFound = CSVData[row -1].find(",", previousFound+1);
            }
            return CSVData[row - 1].substr(previousFound+1,currentFound-(previousFound+1));
        }
    }
    else if (row > numberOfRows() || row < 1) {
        return "invalid row value";
    }
    else if (column > numberOfColumns() || column < 1) {
        return "invalid column value";
    }
    else {
        return "not yet implemented";
    }



}

std::string CsvFile::headerAt(int column) const
{
  // TODO: implement this method. See header for description.

    return at(1, column);

    //return "not yet implemented";
}

int CsvFile::columnIndexOf(const std::string &columnName) const
{
  // TODO: implement this method. See header for description.

    if (!CSVData.empty()){
        for(int i = 0; i < numberOfColumns(); i++){
            if (columnName == at(1,i)){
                return i;
            }
        }
        return 0;
    }
    else {
        return -1;
    }
}

void CsvFile::createCSVFile()
{
    int allColumns = numberOfColumns();
    if(allColumns <= 0)
    {
        return;
    }


    int allRows = numberOfRows();


    for(int i = 1;i < allRows;i++)
    {
        QString allTempStr;
        QString tempStr1 = QString::fromStdString(this->at(i,0));
        m_deviceName.append(tempStr1);
        allTempStr += (tempStr1 + " ");

        tempStr1 = QString::fromStdString(this->at(i,1));
        m_measurementType.append(tempStr1);
        allTempStr += (tempStr1 + " ");

        tempStr1 = QString::fromStdString(this->at(i,2));
        m_timestamp.append(tempStr1);
        allTempStr += (tempStr1 + " ");

        tempStr1 = QString::fromStdString(this->at(i,3));
        m_value.append(tempStr1);
        allTempStr += (tempStr1 + " ");

        tempStr1 = QString::fromStdString(this->at(i,4));
        m_uitOfMEasure.append(tempStr1);
        allTempStr += (tempStr1 + " ");

        tempStr1 = QString::fromStdString(this->at(i,5));
        m_isFiltered.append(tempStr1);
        allTempStr += (tempStr1 + " ");

        tempStr1 = QString::fromStdString(this->at(i,6));
        m_rwaMeasurement.append(tempStr1);
        allTempStr += (tempStr1 + " ");

        tempStr1 = QString::fromStdString(this->at(i,7));
        m_getURL.append(tempStr1);
        allTempStr += (tempStr1 + " ");

        m_getLastSeen.append(allTempStr);
    }

}


QStringList CsvFile::deviceName()
{
    return m_deviceName;
}

QStringList CsvFile::measurementType()
{
    return m_measurementType;
}

QStringList CsvFile::timestamp()
{
    return m_timestamp;
}

QStringList CsvFile::value()
{
    return m_value;
}

QStringList CsvFile::uitOfMEasure()
{
    return m_uitOfMEasure;
}

QStringList CsvFile::isFiltered()
{
    return m_isFiltered;
}

QStringList CsvFile::rwaMeasurement()
{
    return m_rwaMeasurement;
}

QStringList CsvFile::getURL()
{
    return m_getURL;
}

QStringList CsvFile::getLastSeen()
{
#if 0

    for(int i = 0;i < m_deviceName.count();i++)
    {
        QString tempStr;
        tempStr += m_deviceName.at(i) + " ";
        tempStr += m_measurementType.at(i) + " ";
        tempStr += m_timestamp.at(i) + " ";
        tempStr += m_value.at(i) + " ";
        tempStr += m_uitOfMEasure.at(i) + " ";
        tempStr += m_isFiltered.at(i) + " ";
        tempStr += m_rwaMeasurement.at(i) + " ";
        tempStr += m_getURL.at(i) + " ";
        m_getLastSeen.append(tempStr);
    }

#endif
    return m_getLastSeen;
}

