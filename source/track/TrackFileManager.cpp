/*
 * TrackFileManager.cpp
 *
 *  Created on: 17.06.2013
 *      Author: david
 */


#include <dirent.h>

#include "ResourcePath.hpp"
#include "TrackFileManager.h"
#include "TrackFile.h"

void Rac0r::TrackFileManager::load() {
	DIR *trackDirectory;
	struct dirent *dp;
	this->trackList.clear();

	std::vector<Rac0r::TrackFile> trackList;
	std::string trackPath = resourcePath().append(trackDirPath);
	if((trackDirectory = opendir(trackPath.c_str())) != NULL) {
		while((dp = readdir(trackDirectory)) != NULL) {
			std::string trackName = dp->d_name;
			std::string imageName = dp->d_name;
			size_t pos;
			if((pos = trackName.find(".track", 0)) != std::string::npos) {
				this->trackList.push_back(Rac0r::TrackFile(trackPath + trackName, trackPath + imageName));
			}
		}
	}


}

