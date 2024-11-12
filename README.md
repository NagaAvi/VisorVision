# VisterVision - Prototype 0.1

##Progress Report on VisorVision Project

##Main Objective
The main goal of the VisorVision project is to create an AR-based assistive system designed for individuals facing face blindness (prosopagnosia) or short-term memory loss. The system will integrate facial recognition capabilities to provide real-time identification and relevant contextual overlays through a wearable AR device, thereby enhancing daily interactions and independence for users.

##Progress to Date

##Initial System Development:
The initial focus has been on building foundational components for environment understanding and motion detection. This development is crucial for ensuring accurate scene awareness, which is necessary for facial recognition and displaying relevant contextual data.

##Key Features Implemented:
##Environment Detection:
Contour detection and sorting algorithms were developed to identify prominent shapes in the camera feed and display them with highlighted edges. Morphological transformations are applied for noise reduction.

##Object and Motion Detection:
Implemented Canny edge detection and motion detection functionalities to identify object edges and detect movements within the frame. The processed output is displayed in real-time for evaluation and tuning.

##Light Estimation:
Developed a brightness analysis feature that estimates average light levels in the camera’s view, useful for calibrating AR overlays under varying light conditions.

##Smoothing Algorithms:
Integrated a smoothing algorithm to stabilize bounding boxes around detected objects, reducing flickering and improving display stability.

#Current Outputs

- Real-time contour detection and edge detection display.
- Object and motion detection outputs presented alongside light estimation results.
- Environment understanding capability showcased through processed camera frames, with visual overlays for testing and refinement.
- Optimized and stable display with smoothed bounding boxes, enhancing user experience during testing.

#Next Steps

- Facial Recognition Integration:
Collaborate with the API team for integrating facial recognition capabilities. Focus on capturing and processing facial data for accurate identification in real-world scenarios.

- AR Overlay Development:
Develop AR overlays that can display identifying information in real time, using Unity to support cross-platform functionality.

- Hardware and Component Selection:
Complete testing of hardware components like the ESP32-Cam modules for effective integration with mobile devices.

- Prototype Creation:
Build a prototype showcasing a working AR glasses system with facial recognition for demo purposes.

- System Optimization:
Focus on optimizing real-time performance, reducing latency, and enhancing detection accuracy to ensure seamless user experiences.
