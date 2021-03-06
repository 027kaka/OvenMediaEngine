//==============================================================================
//
//  RtmpProvider
//
//  Created by Kwon Keuk Han
//  Copyright (c) 2018 AirenSoft. All rights reserved.
//
//==============================================================================

#include "rtmp_application.h"
#include "rtmp_stream.h"

#include "base/provider/application.h"
#include "base/info/stream.h"

#define OV_LOG_TAG "RtmpApplication"

std::shared_ptr<RtmpApplication> RtmpApplication::Create(const info::Application &application_info)
{
	auto application = std::make_shared<RtmpApplication>(application_info);
	application->Start();
	return application;
}

RtmpApplication::RtmpApplication(const info::Application &application_info)
	: Application(application_info)
{
}

// Create Stream
std::shared_ptr<pvd::Stream> RtmpApplication::CreateStream()
{
	logtd("OnCreateStream");

	auto stream = RtmpStream::Create(GetSharedPtrAs<pvd::Application>());

	return stream;
}
