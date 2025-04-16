//HEADER

#include "Api.hpp"

Api::Api(void) {}

Api::Api(const Api &rhs) {
	(void)rhs;
}

Api &Api::operator=(const Api &rhs) {
	(void)rhs;
	return (*this);
}

Api::~Api(void) {}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* output) {
    size_t totalSize = size * nmemb;
    ((std::string*)output)->append((char*)contents, totalSize);
    return totalSize;
}

void Api::apiRequest(const std::string &login) {
	(void)login;
	CURL *curl = curl_easy_init();
	if (!curl) {
		std::cerr << "init failed\n";
		return;
	}

    curl_easy_setopt(curl, CURLOPT_URL, "https://api.intra.42.fr/oauth/token");
    curl_easy_setopt(curl, CURLOPT_POST, 1L);

	const std::string &client_id =
		"u-s4t2ud-ad20c0580b5b2d1e67736549dd536f87146a2340a5cbd41aba0c1da8655e0293";
	const std::string &client_secret =
		"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";
    const std::string &grant_type = "client_credentials";
	std::string post_fields = "grant_type=" + grant_type + "&client_id=" + client_id + "&client_secret=" + client_secret;
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());

    std::string response_data;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

    // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

	CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        return;
    }

    std::cout << "response: " << response_data << std::endl;
	curl_easy_cleanup(curl);
}

// curl -X POST --data "grant_type=client_credentials&client_id=u-s4t2ud-ad20c0580b5b2d1e67736549dd536f87146a2340a5cbd41aba0c1da8655e0293&client_secret=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" https://api.intra.42.fr/oauth/token | jq