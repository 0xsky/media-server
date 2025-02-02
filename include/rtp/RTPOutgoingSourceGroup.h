#ifndef RTPOUTGOINGSOURCEGROUP_H
#define RTPOUTGOINGSOURCEGROUP_H

#include <string>
#include <map>
#include <set>

#include "config.h"
#include "rtp/RTPPacket.h"
#include "rtp/RTPOutgoingSource.h"
#include "TimeService.h"

struct RTPOutgoingSourceGroup
{
public:
	class Listener 
	{
		public:
			virtual void onPLIRequest(RTPOutgoingSourceGroup* group,DWORD ssrc) = 0;
			virtual void onREMB(RTPOutgoingSourceGroup* group,DWORD ssrc,DWORD bitrate) = 0;
		
	};
public:
	RTPOutgoingSourceGroup(MediaFrame::Type type,TimeService& timeService);
	RTPOutgoingSourceGroup(std::string &mid,MediaFrame::Type type, TimeService& timeService);
	
	void AddListener(Listener* listener);
	void RemoveListener(Listener* listener);
	void onPLIRequest(DWORD ssrc);
	void onREMB(DWORD ssrc,DWORD bitrate);
	TimeService& GetTimeService()	{ return timeService; }
	RTPOutgoingSource* GetSource(DWORD ssrc);
	
	void Update(QWORD now);
	void Update();
	//RTX packets
	void AddPacket(const RTPPacket::shared& packet);
	RTPPacket::shared GetPacket(WORD seq) const;
	void ReleasePackets(QWORD until);
	void ReleasePacketsByTimestamp(QWORD until);
	void ReleaseAllPackets();
	
	
	
public:	
	std::string mid;
	MediaFrame::Type type;
	RTPOutgoingSource media;
	RTPOutgoingSource rtx;
private:	
	TimeService& timeService;
	std::map<DWORD,RTPPacket::shared> packets;
	std::set<Listener*> listeners;
};


#endif /* RTPOUTGOINGSOURCEGROUP_H */

