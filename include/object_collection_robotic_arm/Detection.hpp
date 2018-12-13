/*
 * BSD 3-Clause LICENSE
 *
 * Copyright (c) 2018, Anirudh Topiwala
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without  
 * modification, are permitted provided that the following conditions are 
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, 
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright 
 * notice, this list of conditions and the following disclaimer in the   
 * documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its 
 * contributors may be used to endorse or promote products derived from this 
 * software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS 
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
 * THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * @file Detection.hpp
 * @brief This is the declaration of the Detection class
 * @author Ashwin Goyal [Ghost1995] - driver
 * @author Anirudh Topiwala [anirudhtopiwala] - navigator
 * @date Nov 27, 2018
 */

#ifndef INCLUDE_OBJECT_COLLECTION_ROBOTIC_ARM_DETECTION_HPP_
#define INCLUDE_OBJECT_COLLECTION_ROBOTIC_ARM_DETECTION_HPP_

#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <string>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include "KukaKinematics.hpp"

/*
 * @brief Detection is a class used for working with the camera in the world
 */
class Detection {
 private:
    // ROS node handle
    ros::NodeHandle n;
    // A cv_bridge variable to convert sensor_imgs data to readable openCV data
    image_transport::ImageTransport imgT;
    // It is a subscriber for the Image Transport data
    image_transport::Subscriber imageSubscriber;
    // It is the variable to read image data
    cv_bridge::CvImagePtr cv_ptr;
    // It is a variable denoting the name of the image window
    const std::string OPENCV_WINDOW = "Image Window";
    // It is a KukaKinematics class object
    KukaKinematics & kuka;

    /**
     * @brief This is a private method of this class. It is the image callback
     *        function which reads the image captured by the camera sensor.
     *
     * @param This method takes the message being published to the 'camera_raw'
     *        topic as input.
     *
     * @return This method does not return any argument. It simply reads the
     *         image and assigns the value to the respective variable.
     */
    void readImg(const sensor_msgs::ImageConstPtr &);

 public:
    /*
     * @brief This is the constructor for the class
     */
    explicit Detection(KukaKinematics &);

    /*
     * @brief This is the first method of the class. It detects the position
     *        of a particularly colored object.
     *
     * @param This function takes colour of the object as input.
     *
     * @result This function returns the positions for that object.
     */
    std::vector<KukaKinematics::States> colorThresholder(const std::string &);

    /*
     * @brief This is the destructor for the class
     */
    ~Detection();
};

#endif  // INCLUDE_OBJECT_COLLECTION_ROBOTIC_ARM_DETECTION_HPP_
