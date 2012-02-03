#ifndef FILEDATA_H_
#define FILEDATA_H_

#include <cstddef>
#include <string>


namespace ewok {


  class FileData {
  public:
    FileData();
    FileData(const std::string &filename);
    // ~FileData();
    
    void setData(const std::string &name, char *bytes, size_t size);
    void read(const std::string &filename);

    const std::string &name() const;
    size_t size() const;
    const char *bytes() const;

    void erase();
  
  private:
    // FileData(const FileData &);
    // FileData& operator=(const FileData &);

    std::string name_;
    size_t size_;
    char *bytes_;
  };


} // namespace ewok


#endif  // FILEDATA_H_
