#include <utility>

//==============================================================================
//
//  Transcoder
//
//  Created by Kwon Keuk Han
//  Copyright (c) 2018 AirenSoft. All rights reserved.
//
//==============================================================================

#include <iostream>
#include <unistd.h>

#include "transcoder.h"
#include "config/config_manager.h"

#define OV_LOG_TAG "Transcoder"

std::shared_ptr<Transcoder> Transcoder::Create(std::shared_ptr<MediaRouteInterface> router)
{
	auto transcoder = std::make_shared<Transcoder>(router);
	if (!transcoder->Start())
	{
		logte("An error occurred while creating Transcoder");
		return nullptr;
	}
	return transcoder;
}

std::shared_ptr<Transcoder> Transcoder::Create(const std::vector<info::Application> &application_list, std::shared_ptr<MediaRouteInterface> router)
{
	auto transcoder = std::make_shared<Transcoder>(application_list, router);
	if (!transcoder->Start())
	{
		logte("An error occurred while creating Transcoder");
		return nullptr;
	}
	return transcoder;
}

Transcoder::Transcoder(std::shared_ptr<MediaRouteInterface> router)
{
	_router = std::move(router);
}

Transcoder::Transcoder(const std::vector<info::Application> &application_list, std::shared_ptr<MediaRouteInterface> router)
{
	_app_info_list = application_list;
	_router = std::move(router);
}

bool Transcoder::Start()
{
	// av_log_set_level(AV_LOG_TRACE);

	logtd("Started media trancode modules.");

	if(CreateApplications() == false)
	{
		logte("Failed to start media transcode modules. invalid application.");

		return false;
	}

	return true;
}

bool Transcoder::Stop()
{
	logtd("Terminated media transcode modules.");

	if(!DeleteApplications())
	{
		return false;
	}

	// TODO: 패킷 처리 스레드를 만들어야함.. 어플리케이션 단위로 만들어 버릴까?
	return true;
}

// Create Application
bool Transcoder::OnCreateApplication(const info::Application &app_info)
{
	info::application_id_t application_id = app_info.GetId();

	auto trans_app = std::make_shared<TranscodeApplication>(app_info);

	// 라우터 어플리케이션 관리 항목에 추가
	_tracode_apps[application_id] = trans_app;

	_router->RegisterObserverApp(app_info, trans_app);
	_router->RegisterConnectorApp(app_info, trans_app);

	return true;
}

// Delete Application
bool Transcoder::OnDeleteApplication(const info::Application &app_info)
{
	return true;
}

// Create Application
//  @called by main function
bool Transcoder::CreateApplication(info::Application application_info)
{

	return true;
}

bool Transcoder::CreateApplications()
{
	for(auto const &application_info : _app_info_list)
	{
		info::application_id_t application_id = application_info.GetId();

		auto trans_app = std::make_shared<TranscodeApplication>(application_info);

		// 라우터 어플리케이션 관리 항목에 추가
		_tracode_apps[application_id] = trans_app;

		_router->RegisterObserverApp(application_info, trans_app);
		_router->RegisterConnectorApp(application_info, trans_app);
	}

	return true;
}

// 어플리케이션의 스트림이 삭제됨
bool Transcoder::DeleteApplications()
{
	return true;
}

//  Application Name으로 TranscodeApplication 찾음
std::shared_ptr<TranscodeApplication> Transcoder::GetApplicationById(info::application_id_t application_id)
{
	auto obj = _tracode_apps.find(application_id);

	if(obj == _tracode_apps.end())
	{
		return nullptr;
	}

	return obj->second;
}
