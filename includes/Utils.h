#include <string>
class Utils
{
    public:
        static int Utils::BytesToInt(unsigned char* data, int len);
		static std::string ByteArrayToHexString(unsigned char* arrChData, size_t len);
};