# VisterVision - Prototype 0.1

# Project Overview
The VisorVision project aims to create an Augmented Reality (AR) assistive system for individuals with prosopagnosia (face blindness) or short-term memory loss. This system will leverage facial recognition technology to provide real-time identification and relevant contextual information through a wearable AR device, ultimately enhancing daily interactions and fostering independence for users.

## Progress
### Initial System Development:
#### Environment Understanding:
Implemented algorithms for contour detection and sorting to identify prominent shapes in the camera feed (highlighted edges).
Morphological transformations applied for noise reduction.
#### Object and Motion Detection:
Developed functionalities for Canny edge detection and motion detection to identify object edges and movement within the frame.
Processed outputs displayed in real-time for evaluation and tuning.
#### Light Estimation:
Implemented a brightness analysis feature to estimate average light levels in the camera's view, enabling calibration for AR overlays under various lighting conditions.
#### Smoothing Algorithms:
Integrated a smoothing algorithm to stabilize bounding boxes around detected objects, reducing flickering and improving display stability.

## Current Outputs:
- Real-time display of contour and edge detection
- Object and motion detection outputs alongside light estimation results
- Processed camera frames showcasing environment understanding capabilities with visual overlays for testing and refinement
- Optimized and stable display with smoothed bounding boxes for enhanced user experience during testing

## Next Steps
- Facial Recognition Integration: Collaboration with the API team to integrate facial recognition capabilities, focusing on capturing and processing facial data for accurate identification in real-world scenarios.
- AR Overlay Development: Developing AR overlays using Unity to display identifying information in real time, ensuring cross-platform functionality.
- Hardware and Component Selection: Completing testing of hardware components such as ESP32-Cam modules to facilitate smooth integration with mobile devices.
- Prototype Creation: Building a working prototype showcasing a functional AR glasses system with facial recognition for demonstration purposes.
- System Optimization: Focus on optimizing real-time performance, minimizing latency, and enhancing detection accuracy to ensure a seamless user experience.

## License
Specify the license under which the project is distributed (e.g., MIT License).
