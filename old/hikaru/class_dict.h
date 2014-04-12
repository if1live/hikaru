// Ŭnicode please
#pragma once

namespace hikaru {;

class ClassAttribute;

class ClassDict {
public:
  static ClassDict &GetInstance();
  ClassDict();
  ~ClassDict();

  bool Register(ClassAttribute *class_attr);
  int GetLatestVersion(const std::string &family_name) const;
  bool SetLatestVersion(const std::string &family_name, int version);

  ClassAttribute *GetLatestVersionClassAttribute(const std::string &family_name);
  ClassAttribute *GetClassAttribute(const std::string &family_name, int version);

  std::vector<ClassAttribute*> GetTotalData() const;
private:
  //key : family 
  std::multimap<std::string, ClassAttribute*> class_attr_dict_;
  //key : family 
  //value : latest version
  std::map<std::string, int> latest_version_dict_;
};
}
