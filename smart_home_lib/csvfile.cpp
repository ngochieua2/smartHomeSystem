#include "csvfile.h"

using namespace data;

CsvFile::CsvFile(std::istream &input)
{
    while(!input.eof()){
        rows ++;
        std::string str;
        getline(input,str);
        std::vector<std::string> item;
        QString qstr = QString::fromStdString(str);
        QStringList strList = qstr.split(",");
        for(int i=0;i<strList.length();i++){
            item.push_back(strList[i].toStdString());
            cols = i+1;
        }
        dataSet.push_back(item);
    }
}

int CsvFile::numberOfColumns() const
{

  return cols;
}

int CsvFile::numberOfRows() const
{
  return rows;
}

std::string CsvFile::at(int row, int column) const
{
  int x = row - 1;
  int y = column - 1;
  if(x < 0 || y < 0 || x >= rows || y >= cols){
      return "not yet implemented";
  }
  std::vector<std::string> item = dataSet[x];
  return item[y];
}

std::string CsvFile::headerAt(int column) const
{
    int cc = column - 1;
    if(cc < 0 || cc >= cols){
        return "not yet implemented";
    }
  // TODO: implement this method. See header for description.
    std::vector<std::string> item = dataSet[0];
    return item[cc];
}

int CsvFile::columnIndexOf(const std::string &columnName) const
{
  for(int i=0;i<dataSet.size();i++){
       std::vector<std::string> item = dataSet[i];
      if(columnName == item[0]){
          return i+1;
      }
  }
  return -1;
}

QString CsvFile::getUrl(){
    int key = columnIndexOf("url");
    std::vector<std::string> item = dataSet[key];
    return QString::fromStdString(item[1]);
}
QString CsvFile::getLastSeen(){
    int key = columnIndexOf("lastseen");
    std::vector<std::string> item = dataSet[key];
    return QString::fromStdString(item[1]);
}
QString CsvFile::createCSVFile(){

}
QString CsvFile::deviceName(){
    int key = columnIndexOf("devicename");
    std::vector<std::string> item = dataSet[key];
    return QString::fromStdString(item[1]);
}
int CsvFile::measurementType(){
    int key = columnIndexOf("type");
    std::vector<std::string> item = dataSet[key];
    return QString::fromStdString(item[1]).toInt();
}
long CsvFile::timestamp(){
    int key = columnIndexOf("timestamp");
    std::vector<std::string> item = dataSet[key];
    return QString::fromStdString(item[1]).toLong();
}
QVariant CsvFile::value(){
    int key = columnIndexOf("value");
    std::vector<std::string> item = dataSet[key];
    return QString::fromStdString(item[1]).toInt();
}
QString CsvFile::unitOfMEasure(){
    int key = columnIndexOf("unitofmeasure");
    std::vector<std::string> item = dataSet[key];
    return QString::fromStdString(item[1]);
}
bool CsvFile::isFiltered(){
    int key = columnIndexOf("filtered");
    std::vector<std::string> item = dataSet[key];
    QString filtered =  QString::fromStdString(item[1]);
    if(filtered == "true"){
        return true;
    }
    return false;
}
