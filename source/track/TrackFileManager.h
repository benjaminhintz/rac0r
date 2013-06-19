//
//  TrackFileManager.h
//  Rac0r
//
//  Created and copyright by
//  Benjamin Hintz
//  Florian Kaluschke
//  Jannes Meyer
//  David Leska
//  Lars Peterke
//  Jan Schulte
//  on Jun 2013. All rights reserved.
//

#ifndef TRACKFILEMANAGER_H_
#define TRACKFILEMANAGER_H_

#include <vector>
#include "TrackFile.h"

namespace Rac0r {
	class TrackFileManager {
	public:
		TrackFileManager(){}
		virtual ~TrackFileManager(){}
		void load();
		std::vector<Rac0r::TrackFile> & getTrackList() { load(); return this->trackList; }
	private:
		std::vector<Rac0r::TrackFile> trackList;

		#ifdef __linux
		std::string trackDirPath = "tracks/";
		#endif
		#ifdef __APPLE__
		std::string trackDirPath = "";
		#endif
	};
} // namespace Rac0r
#endif /* TRACKFILEMANAGER_H_ */
