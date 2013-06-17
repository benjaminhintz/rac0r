/*
 * TrackFile.h
 *
 *  Created on: 17.06.2013
 *      Author: david
 */

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
