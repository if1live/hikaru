// Ŭnicode please
#pragma once

#include <string>
#include <vector>

namespace hikaru {;
struct BaseData;

typedef enum {
  kMemberAttributeNone,
  kMemberAttributeBool,
  kMemberAttributeString,
  kMemberAttributeInt,
  kMemberAttributeFloat,
  kMemberAttributeStringList,
  ///@def 몇가지 문자열중 1개만으로 설정해야되는 경우
  ///제약을 걸때 사용됨
  kMemberAttributeStringEnum,
  kMemberAttributeCount,
} MemberAttributeType;

template<typename T> struct MemberType2Type { enum { type = kMemberAttributeNone }; };
template<> struct MemberType2Type<int> { enum { type = kMemberAttributeInt }; };
template<> struct MemberType2Type<bool> { enum { type = kMemberAttributeBool }; };
template<> struct MemberType2Type<float> { enum { type = kMemberAttributeFloat }; };
template<> struct MemberType2Type<std::string> { enum { type = kMemberAttributeString }; };
template<> struct MemberType2Type< std::vector<std::string> > { enum { type = kMemberAttributeStringList }; };

class MemberAttribute {
public:
  template<typename T2T>
  static MemberAttribute Create(const std::string &name, int offset, T2T) {
    MemberAttributeType attr_type = (MemberAttributeType)T2T::type;
    if(attr_type == kMemberAttributeNone) {
      HKASSERT(false);
      return MemberAttribute();
    } else {
      return MemberAttribute(name, attr_type, offset);
    }
  }
  static MemberAttribute StringEnum(const std::string &name, int offset);

public:
  MemberAttribute(const std::string &name, MemberAttributeType type, int offset);
  MemberAttribute();
  ~MemberAttribute();

  const std::string &name() const { return name_ ; }
  int offset() const { return offset_; }
  MemberAttributeType type() const { return type_; }
  //enum을 사용하는 타입인가 아닌가
  bool IsUseEnum() const;

private:
  int offset_;
  MemberAttributeType type_;
  std::string name_;

  //어차피 맵에디터쪽에서만쓴다면 상속같은 귀찮은거 생각하지 않고 때려박고 안쓰는것도 좋을듯
  //상속을 넣으면 메모리 관리같은거때문에 구조가 우주로 가기 쉽다(그리고 이전버전은 그랫고)
public:
  typedef std::vector<std::string> StrEnumListType;
  bool AddStringEnum(const std::string &key);
  int GetEnumCount() const { return str_enum_list_.size(); }
  bool IsValidStrEnum(const std::string &name) const;
  const std::string &GetDefaultStrEnum() const;
  const StrEnumListType &str_enum_list() const { return str_enum_list_; }

private:
  StrEnumListType str_enum_list_;
};


template<typename T> struct TypeInfo { };

class ClassAttribute {
public:
  typedef std::vector<MemberAttribute> MemberAttributeList;
  typedef MemberAttributeList::iterator iterator;
  typedef MemberAttributeList::const_iterator const_iterator;

public:
  template<typename T>
  ClassAttribute(const TypeInfo<T>&)
    : family_name_(T::FamilyName()), 
    version_(T::version),
    wrapper_(new TypeWrapperImpl<T>()) { }
  ~ClassAttribute() {}

  int version() const { return version_; }
  const std::string &family_name() const { return family_name_; }
  
  // member attribute관련
  int MemberCount() const { return mem_attr_list_.size(); }
  bool AddMember(const MemberAttribute &attr);
  
  iterator begin() { return mem_attr_list_.begin(); }
  const_iterator begin() const { return mem_attr_list_.begin(); }
  iterator end() { return mem_attr_list_.end(); }
  const_iterator end() const { return mem_attr_list_.end(); }

  BaseData *Create() { return wrapper_->Create(); }
  unsigned int ClassCode() const { return wrapper_->ClassCode(); }
  unsigned int FamilyCode() const { return wrapper_->FamilyCode(); }

private:
  //실제 객체 생성과 같은것을 시킬수 있는 부분
  struct TypeWrapper {
    virtual BaseData *Create() const = 0;
    virtual unsigned int ClassCode() const = 0;
    virtual unsigned int FamilyCode() const = 0;
  };

  template<typename T>
  struct TypeWrapperImpl : public TypeWrapper {
    BaseData *Create() const { return new T(); }
    unsigned int ClassCode() const { return T::ClassCode(); }
    unsigned int FamilyCode() const { return T::FamilyCode(); }
  };

private:
  std::string family_name_;
  int version_;
  MemberAttributeList mem_attr_list_;
  std::unique_ptr<TypeWrapper> wrapper_;
};

} //namespace hikaru
