#ifndef __HIKARU_H__
#define __HIKARU_H__

#include <string>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <memory>
#include <set>
#include <cassert>
#include <cstddef>

namespace hikaru {
    enum AttributeType {
        None,
        Bool,
        Int,
        Float,
        // String,
    };

    // http://stackoverflow.com/questions/13180842/how-to-calculate-offset-of-a-class-member-at-compile-time
    template<typename T, typename U> constexpr size_t offsetOf(U T::*member)
    {
        return (char*)&((T*)nullptr->*member) - (char*)nullptr;
    }


    struct RSHash {
        static unsigned int Hash(const char *str) {
            unsigned int b = 378551;
            unsigned int a = 63689;
            unsigned int hash = 0;

            size_t length = strlen(str);
            for (size_t i = 0; i < length; i++) {
                hash = hash * a + str[i];
                a = a * b;
            }

            return (hash & 0x7FFFFFFF);
        }
    };


    class BaseStruct {
    public:
        typedef hikaru::RSHash HashFunc;

        BaseStruct() : class_hash_(0), base_hash_(0) {}
        virtual ~BaseStruct() {}

        virtual BaseStruct *clone() const = 0;

    protected:
        // class name based hash. unique value
        unsigned int class_hash_;
        // parent hash. If group is same, parent hash are same.
        unsigned int base_hash_;
    };


    class FieldAttribute {
    public:
        FieldAttribute(const char *name, AttributeType type, int offset)
            : name_(name), type_(type), offset_(offset) { }
        FieldAttribute() : name_(""), type_(AttributeType::None), offset_(0) {}

        ~FieldAttribute() {}

        const std::string &name() const { return name_; }
        int offset() const { return offset_; }
        AttributeType type() const { return type_; }

    private:
        int offset_;
        AttributeType type_;
        std::string name_;

        // factory
    public:
#define ATTRIBUTE_FACTORY(NAME, TYPE) \
	static FieldAttribute NAME(const char *name, int offset) {	\
		return FieldAttribute(name, TYPE, offset);	\
		}

        ATTRIBUTE_FACTORY(createInt, AttributeType::Int)
            ATTRIBUTE_FACTORY(createBool, AttributeType::Bool)
            ATTRIBUTE_FACTORY(createFloat, AttributeType::Float)
#undef ATTRIBUTE_FACTORY
    };



    class ClassAttribute {
    public:
        typedef std::vector<FieldAttribute> attribute_list_t;
        typedef attribute_list_t::iterator iterator;
        typedef attribute_list_t::const_iterator const_iterator;
    public:
        ClassAttribute(const char *base_name, const char *class_name, int version)
            : base_name_(base_name),
            class_name_(class_name),
            version_(version) {	}

        ~ClassAttribute() {
            //class dict�� ��ϵ� �������� �Ҹ���/�����ڰ� ���� �Ұ����ϴϱ� ������ ���� ����
            //������ Ŭ������ 1ȸ ��ϵ� ������ �Ȼ����״ϱ� ū ������ �������̴�
        }

        unsigned int hash() const {
            return RSHash::Hash(class_name_.data());
        }

        void set_prototype(BaseStruct *data) {
            prototype_.reset(data);
        }

        const std::string &base_name() const { return base_name_; }
        const std::string &class_name() const { return class_name_; }
        int version() const { return version_; }

        BaseStruct *clone() const {
            if (prototype_.get() != nullptr) {
                return prototype_->clone();
            }
            return nullptr;
        }

        //attribute��� + �˻�
        bool add(const FieldAttribute &attr) {
            if (isAttributeExist(attr.name()) == false) {
                attr_list_.push_back(attr);
                return true;
            }
            else {
                return false;
            }
        }

        bool isAttributeExist(const std::string &attr_name) const {
            auto it = attr_list_.begin();
            auto endit = attr_list_.end();
            for (; it != endit; ++it) {
                if (it->name() == attr_name) {
                    return true;
                }
            }
            return false;
        }

        FieldAttribute *get(const std::string &attr_name) {
            auto it = attr_list_.begin();
            auto endit = attr_list_.end();
            for (; it != endit; ++it) {
                if (it->name() == attr_name) {
                    return &(*it);
                }
            }
            return nullptr;
        }
        int count() const { return attr_list_.size(); }

        const_iterator begin() const { return attr_list_.begin(); }
        const_iterator end() const { return attr_list_.end(); }
        iterator begin() { return attr_list_.begin(); }
        iterator end() { return attr_list_.end(); }

    private:
        std::string base_name_;
        std::string class_name_;
        int version_;

        std::shared_ptr<BaseStruct> prototype_;

        attribute_list_t attr_list_;
    };



    //Ŭ�����̸�-attribute�� ����Ǵϱ�
    //�߰�Ŭ������ �����ؼ� ���⵵�� �ø��⺸��
    //multimap���� ������ ����� �����Ű���
    //�� Ŭ���� �ϳ��� Ŭ������밡���� Ŭ���� ���. ���ο� ����մ� ������ϱ���
    //���� ������. �̰� ���� Ŭ������ ������ �װ͵� �װ� ������� ������ ���Ű��Ƽ�..
    class ClassDict {
    public:
        static ClassDict &getInstance() {
            static ClassDict ctx;
            return ctx;
        }

    public:
        //������Ʈ���� ������ �հ� �������� �������� ������ ����� �����ϱ� �̷��� 
        //������ �ϳ� �߰��ؼ� ������ ������ ���� �յ����޴�
        //key : BeltHeader
        //value : pair<VeltHeader_v1, 1> ���� ������ �ǵ�����
        typedef std::unordered_multimap<std::string, std::pair<std::string, int>> VersionDictType;
        typedef std::vector<ClassAttribute> ClassAttributeListType;

    public:
        ClassDict() {}
        ~ClassDict() {}
        void clear() {
            class_attr_list_.clear();
            version_dict_.clear();
        }

        // BeltHeader, BeltHeader_v1, 1 ���� Ư�� Ŭ������ ���� �̸��� ����ؼ� ������ �յ�������
        // �̰� �Ǿ� ������/�ٿ��� �Ҽ� �����Ű���
        void setClassVersionInfo(const std::string &base_name, const std::string &class_name, int version) {
            auto version_pair = make_pair(class_name, version);
            version_dict_.insert(make_pair(base_name, version_pair));
        }

        bool isBaseClassExist(const std::string &base_name) const {
            auto found = version_dict_.find(base_name);
            return (found != version_dict_.end());
        }

        std::string getLatestClassName(const std::string &base_name) const {
            auto ret = version_dict_.equal_range(base_name);
            if (ret.first == version_dict_.end()) {
                static std::string empty;
                return empty;
            }
            std::string latest_name;
            int version = -1;
            for (auto it = ret.first; it != ret.second; ++it) {
                if (it->second.second > version) {
                    latest_name = it->second.first;
                    version = it->second.second;
                }
            }
            return latest_name;
        }

        bool isLatestClassName(const std::string &class_name) const {
            //version �������� ������ �ܱ�
            auto it = version_dict_.begin();
            auto endit = version_dict_.end();
            int curr_version = -1;
            for (; it != endit; ++it) {
                if (it->second.first == class_name) {
                    curr_version = it->second.second;
                    break;
                }
            }
            assert(curr_version != -1);

            std::string lastest_name = getLatestClassName(it->first);
            if (lastest_name == it->second.first) {
                return true;
            }
            else {
                return false;
            }
        }

        //Ư�� base class�� Ư�� ������ Ŭ���� �̸� ���
        //�̸� ���� ��Ģ�� ��򰡿� ��� �� ���
        //��ũ�ζ�簡�� ��ĥ�� �������Ű��Ƽ� ������ �и���
        //��ã���� �� ���ڿ�
        std::string getClassName(const std::string &base_name, int version) const {
            auto ret = version_dict_.equal_range(base_name);
            if (ret.first == version_dict_.end()) {
                return std::string("");
            }
            for (auto it = ret.first; it != ret.second; ++it) {
                if (it->second.second == version) {
                    return it->second.first;
                }
            }
            return std::string("");
        }


        //����ü Ŭ���� �̸� ���
        bool isClassExist(const std::string &class_name) const {
            auto it = version_dict_.begin();
            auto endit = version_dict_.end();
            for (; it != endit; ++it) {
                if (it->second.first == class_name) {
                    return true;
                }
            }
            return false;
        }

        ClassAttribute *get(const std::string &class_name) {
            auto it = class_attr_list_.begin();
            auto endit = class_attr_list_.end();
            for (; it != endit; ++it) {
                if (it->class_name() == class_name) {
                    return &(*it);
                }
            }
            return nullptr;
        }

        ClassAttribute *get(unsigned int hash) {
            auto it = class_attr_list_.begin();
            auto endit = class_attr_list_.end();
            for (; it != endit; ++it) {
                if (it->hash() == hash) {
                    return &(*it);
                }
            }
            return nullptr;
        }


        const ClassAttribute *get(unsigned int hash) const {
            auto it = class_attr_list_.begin();
            auto endit = class_attr_list_.end();
            for (; it != endit; ++it) {
                if (it->hash() == hash) {
                    return &(*it);
                }
            }
            return nullptr;
        }

        const ClassAttribute *get(const std::string &class_name) const {
            auto it = class_attr_list_.begin();
            auto endit = class_attr_list_.end();
            for (; it != endit; ++it) {
                if (it->class_name() == class_name) {
                    return &(*it);
                }
            }
            return nullptr;
        }

        bool add(const ClassAttribute &class_attr) {
            auto it = class_attr_list_.begin();
            auto endit = class_attr_list_.end();
            for (; it != endit; ++it) {
                if (it->class_name() == class_attr.class_name()) {
                    //���� �̸� Ŭ���� �߰� �Ұ���
                    return false;
                }
            }
            class_attr_list_.push_back(class_attr);
            //Ŭ���� �߰��ɶ� ������ ������� ������ ��ü ����
            setClassVersionInfo(class_attr.base_name(), class_attr.class_name(), class_attr.version());
            return true;
        }


        std::set<std::string> getBaseClassList() const {
            std::set<std::string> class_set;
            auto it = version_dict_.begin();
            auto endit = version_dict_.end();
            for (; it != endit; ++it) {
                class_set.insert(it->first);
            }
            return class_set;
        }

    private:
        VersionDictType version_dict_;
        ClassAttributeListType class_attr_list_;
    };
}


//#define HIKARU_DEV 1
#define HIKARU_DEV 0


#endif  // __HIKARU_H__
