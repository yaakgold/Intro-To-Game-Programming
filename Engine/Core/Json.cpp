#include "pch.h"
#include "Json.h"
#include <istreamwrapper.h>

namespace hummus
{
    namespace json
    {
        bool Load(const std::string& filename, rapidjson::Document& document)
        {
            bool success = false;

            std::ifstream stream(filename);
            if (stream.is_open())
            {
                rapidjson::IStreamWrapper istream(stream); 
                document.ParseStream(istream);      
                success = document.IsObject();
            }

            return success;
        }

        //integer
        bool Get(const rapidjson::Value& value, const std::string& name, int& data)
        {
            auto iter = value.FindMember(name.c_str());
            if (iter == value.MemberEnd())
            {
                return false;
            }

            auto& property = iter->value;
            if (property.IsInt() == false)
            {
                return false;
            }

            data = property.GetInt();

            return true;
        }

        //float
        bool Get(const rapidjson::Value& value, const std::string& name, float& data)
        {
            auto iter = value.FindMember(name.c_str());
            if (iter == value.MemberEnd())
            {
                return false;
            }

            auto& property = iter->value;
            if (property.IsFloat() == false)
            {
                return false;
            }

            data = property.GetFloat();

            return true;
        }

        //bool
        bool Get(const rapidjson::Value& value, const std::string& name, bool& data)
        {
            auto iter = value.FindMember(name.c_str());
            if (iter == value.MemberEnd())
            {
                return false;
            }

            auto& property = iter->value;
            if (property.IsBool() == false)
            {
                return false;
            }

            data = property.GetBool();

            return true;
        }

        //string
        bool Get(const rapidjson::Value& value, const std::string& name, std::string& data)
        {
            auto iter = value.FindMember(name.c_str());
            if (iter == value.MemberEnd())
            {
                return false;
            }

            auto& property = iter->value;
            if (property.IsString() == false)
            {
                return false;
            }

            data = property.GetString();

            return true;
        }

        //Vector2
        bool Get(const rapidjson::Value& value, const std::string& name, Vector2& data)
        {
            auto iter = value.FindMember(name.c_str());
            if (iter == value.MemberEnd())
            {
                return false;
            }

            auto& property = iter->value;
            if (property.IsArray() == false || property.Size() != 2)
            {
                return false;
            }

            for (rapidjson::SizeType i = 0; i < 2; i++)
            {
                if (property[i].IsNumber() == false)
                {
                    return false;
                }
            }

            data.x = property[0].GetFloat();
            data.y = property[1].GetFloat();

            return true;
        }

        //Color
        bool Get(const rapidjson::Value& value, const std::string& name, Color& data)
        {
            auto iter = value.FindMember(name.c_str());
            if (iter == value.MemberEnd())
            {
                return false;
            }

            auto& property = iter->value;
            if (property.IsArray() == false || property.Size() != 4)
            {
                return false;
            }

            for (rapidjson::SizeType i = 0; i < 4; i++)
            {
                if (property[i].IsNumber() == false)
                {
                    return false;
                }
            }

            data.r = property[0].GetFloat();
            data.g = property[1].GetFloat();
            data.b = property[2].GetFloat();
            data.a = property[3].GetFloat();

            return true;
        }
    }
}
