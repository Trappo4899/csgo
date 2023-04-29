#pragma once

class FNV1a
{
private:

    static const uint32_t PRIME = 0x01000193;
    static const uint32_t OFFSET = 0x811c9dc5;

public:

    static const uint32_t hash(const char* string)
    {
        uint32_t hash = 0;

        for (int i = 0; i < strlen(string); ++i)
        {
            if (string[i] == '\0')
            {
                continue;
            }

            hash = hash ^ string[i];
            hash = hash * PRIME;
        }

        return hash;
    }

    static const uint32_t hash(const wchar_t* string)
    {
        uint32_t hash = 0;

        for (int i = 0; i < wcslen(string); ++i)
        {
            if (string[i] == '\0')
            {
                continue;
            }

            hash = hash ^ string[i];
            hash = hash * PRIME;
        }

        return hash;
    }

    static const uint32_t hash(std::string string)
    {
        return hash(string.c_str());
    }

    static const uint32_t hash(std::wstring string)
    {
        return hash(string.c_str());
    }
};

#define HASH( s ) ( FNV1a::hash( s ) )