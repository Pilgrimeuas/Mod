#pragma once
//
// *һ���򵥵����UWP����� http/https ����ʵ��
// *CNGEGE
// *by https://learn.microsoft.com/en-us/windows/uwp/networking/httpclient?source=recommendations
//

//#include <Windows.h>
#include <string>
#include <ppltasks.h>
#include <fstream>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Security.Cryptography.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Web.Http.Headers.h>
#include "Logger.h"
using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Storage::Streams;
using namespace concurrency;
class NetClient {
public:
	int StatusCode;
	Windows::Web::Http::HttpClient httpClient;
	Windows::Web::Http::HttpResponseMessage httpResponseMessage;

public:
	bool StatusSuccess() {
		if (httpResponseMessage) {
			return httpResponseMessage.IsSuccessStatusCode();
		}else {
			return false;
		}
	}

	std::string GetAsyncAsString() {
		try {
			httpResponseMessage.EnsureSuccessStatusCode();
			auto ret = winrt::to_string(httpResponseMessage.Content().ReadAsStringAsync().get());
			httpClient.Close();
			return ret;
		}
		catch (...) {
			return {};
		}
	}

	IBuffer GetAsyncAsBuffer() {
		try {
			httpResponseMessage.EnsureSuccessStatusCode();
			auto readAsBufferAsync = httpResponseMessage.Content().ReadAsBufferAsync();
			//create_task(readAsBufferAsync).wait();
			auto m_response = readAsBufferAsync.GetResults();
			//create_task(m_response).wait();
			httpClient.Close();
			return m_response;
		}
		catch (...) {
			return {};
		}
	}

	/// <summary>
	/// ��IBuffer��д���ļ�
	/// </summary>
	/// <param name="file">����Ҫ�� [Microsoft.MinecraftUWP_8wekyb3d8bbwe] �ļ����µľ���·��,�������</param>
	/// <param name="buff">IBuffer��</param>
	/// <returns>�Ƿ�д��ɹ�</returns>
	static bool WriteFile(std::string file,IBuffer& buff) {
		if (!buff) {
			return false;
		}
		try {
			std::replace(file.begin(), file.end(), '/', '\\');
			auto wstr = winrt::to_hstring(file);
			if (_access(file.c_str(),0)) {
				std::ofstream(file).close();
			}
			Windows::Storage::StorageFile sfile = Windows::Storage::StorageFile::GetFileFromPathAsync(wstr).get();
			Windows::Storage::FileIO::WriteBufferAsync(sfile, buff);
			return true;
		}
		catch (...) {
			return false;
		}
	}

public:
	static NetClient GetAsync(std::string url) {
		NetClient network;
		Uri requestUri{ winrt::to_hstring(url) };
		network.httpResponseMessage = network.httpClient.GetAsync(requestUri).get();
		network.StatusCode = (uint32_t)network.httpResponseMessage.StatusCode();
		return network;
	}

	static NetClient PostAsync(std::string url,std::string json = "{}") {
		NetClient network;
		Uri requestUri{ winrt::to_hstring(url) };
		Windows::Web::Http::HttpStringContent jsonContent(
			//L"{ \"firstName\": \"Eliot\" }",
			winrt::to_hstring(json),
			UnicodeEncoding::Utf8,
			L"application/json");
		network.httpResponseMessage = network.httpClient.PostAsync(requestUri, jsonContent).get();
		network.StatusCode = (uint32_t)network.httpResponseMessage.StatusCode();
		return network;
	}
};
