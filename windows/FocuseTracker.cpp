#include <windows.h>
#include <iostream>
#include <UIAutomation.h>
#include <ole2.h>
#include <string>
#include <locale>
#include <codecvt>
#include "FocuseTracker.h"
// Глобальные переменные
IUIAutomation *g_pAutomation = NULL;

void FocusTracker::InitializeUIAutomation()
{
	if (FAILED(CoCreateInstance(CLSID_CUIAutomation, NULL, CLSCTX_INPROC_SERVER, IID_IUIAutomation, (void **)&g_pAutomation)))
	{
		std::cerr << "Failed to create UI Automation instance." << std::endl;
		exit(1);
	}
}

void FocusTracker::FinalizeUIAutomation()
{
	if (g_pAutomation)
	{
		g_pAutomation->Release();
		g_pAutomation = NULL;
	}
}
std::string FocusTracker::WideStringToUtf8(const std::wstring &wstr)
{
	if (wstr.empty())
		return std::string();
	int count = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, NULL, NULL);
	std::string str(count - 1, 0);
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], count, NULL, NULL);
	return str;
}
FocusTracker::FocusTracker()
{
}
void FocusTracker::HandleMethodCall(
	const flutter::MethodCall<flutter::EncodableValue> &method_call,
	std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result)
{

	if (method_call.method_name().compare("StartTrackingFocus") == 0)
	{
		std::wstring trackedText = this->StartTrackingFocus();
		std::string utf8String = this->WideStringToUtf8(trackedText);
		result->Success(flutter::EncodableValue(utf8String));
	}
	else if (method_call.method_name().compare("InitializeUIAutomation") == 0)
	{
		this->InitializeUIAutomation();
	}
	else if (method_call.method_name().compare("FinalizeUIAutomation") == 0)
	{
		this->FinalizeUIAutomation();
	}
	else if (method_call.method_name().compare("CoUninitialize") == 0)
	{
		CoUninitialize();
	}
	else
	{
		result->NotImplemented();
	}
}

FocusTracker::FocusTracker(flutter::PluginRegistrarWindows *registrar) noexcept
	: registrar_(registrar)
{
	assert(registrar_);

	auto channel =
		std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
			registrar_->messenger(), "flutter/win_plugin/plugin",
			&flutter::StandardMethodCodec::GetInstance());

	channel->SetMethodCallHandler([this](const auto &call, auto result)
								  { HandleMethodCall(call, std::move(result)); });

	channel_ = std::move(channel);
}

FocusTracker::~FocusTracker() noexcept
{

	registrar_ = nullptr;
}

std::wstring FocusTracker::StartTrackingFocus()
{
	std::wstring a = L"Hello world!";
	IUIAutomationElement *pFocusedElement = NULL;
	IUIAutomationTextPattern *pTextPattern = NULL;
	// Массив диапазонов текстового выделения
	IUIAutomationTextRangeArray *pSelection = NULL;

	g_pAutomation->GetFocusedElement(&pFocusedElement);
	if (pFocusedElement)
	{
		pFocusedElement->GetCurrentPattern(UIA_TextPatternId, (IUnknown **)&pTextPattern);
		if (pTextPattern)
		{
			// Получаем выделенный текст
			pTextPattern->GetSelection(&pSelection);
			if (pSelection)
			{
				int count;
				pSelection->get_Length(&count);
				if (count > 0)
				{
					IUIAutomationTextRange *pTextRange = NULL;
					pSelection->GetElement(0, &pTextRange); // Берем первое выделение, если есть несколько
					if (pTextRange)
					{
						BSTR text;
						pTextRange->GetText(-1, &text); // Получаем текст из выделения
						std::wstring processedText = this->RemoveSpaces(std::wstring(text));
						if (processedText.size() > 0)
						{

							std::wcout << L"Selected text: " << processedText << std::endl;
							return processedText;
						}
						SysFreeString(text);
						pTextRange->Release();
					}
				}
				pSelection->Release();
			}
			pTextPattern->Release();
		}
		pFocusedElement->Release();
	}
	return a;
}

std::wstring FocusTracker::RemoveSpaces(const std::wstring &str)
{
	std::wstring result;
	bool foundNonSpace = false;

	for (wchar_t ch : str)
	{
		if (foundNonSpace)
		{
			// Добавляем все символы после первого небелого
			result += ch;
		}
		else if (!iswspace(ch))
		{
			// Находим первый небелый символ и начинаем добавление в result
			foundNonSpace = true;
			result += ch;
		}
	}

	return result;
}