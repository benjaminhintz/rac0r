//
//  TrackFile.h
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

#ifndef TRACKFILE_H_
#define TRACKFILE_H_

namespace Rac0r {
	class TrackFile {
	public:
		TrackFile(const std::string & _track, const std::string & _image) : track(_track), image(_image) {}
		virtual ~TrackFile(){}
		std::string & getTrackFile() {return track;}
		std::string & getImageFile() {return image;}
	private:
		std::string track;
		std::string image;
	};
} // namespace Rac0r


#endif /* TRACKFILE_H_ */
