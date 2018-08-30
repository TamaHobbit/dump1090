#include<exception>

namespace renderer {
	class exception : public std::exception {
	private:
		std::string title, message;

	public:
		exception(std::string t, std::string m){
			title = t;
			message = m;
		}

		std::string GetTitle(){
			return title;
		}

		std::string GetMessage(){
			return message;
		}
	};
}
