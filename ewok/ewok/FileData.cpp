#include "FileData.h"

#include <cstdio>
#include <cstdlib>
#include "Log.h"


namespace ewok {


  FileData::FileData()
    : name_("empty"), size_(0), bytes_(NULL)
  {
  }


  FileData::FileData(const std::string &filename)
    : name_(filename), size_(0), bytes_(NULL)
  {
    read(filename);
  }


  // FileData::~FileData()
  // {
  //   delete[] bytes_;
  // }

  
  void FileData::setData(const std::string &name, char *data, size_t size)
  {
    Assert(size_ == 0 && bytes_ == NULL, "FileData already has data");
    name_ = name;
    bytes_ = data;
    size_ = size;
  }
  
  
  void FileData::read(const std::string &filename)
  {
    LogInfo << "reading file: " << filename;
    Assert(size_ == 0 && bytes_ == NULL, "FileData is already in use");
  
    FILE *f = fopen(filename.c_str(), "rb");
    if (!f) {
      LogError << "cannot open file: " << filename;
      fclose(f);
      return;
    }
  
    fseek(f, 0, SEEK_END);
    size_ = ftell(f);
    rewind(f);
  
    bytes_ = new char[size_];
    size_t result = fread(bytes_, 1, size_, f);
    if (!result) {
      LogError << "cannot read file: " << filename;
      size_ = 0;
    }

    fclose(f);
  }
  
  
  const std::string &FileData::name() const
  {
    return name_;
  }
  

  size_t FileData::size() const
  {
    return size_;
  }


  const char *FileData::bytes() const
  {
    return bytes_;
  }


  void FileData::erase()
  {
    delete[] bytes_;
    bytes_ = NULL;
    size_ = NULL;
  }


} // namespace ewok
