# Washroom Quality Monitoring Automation
This project aims to revolutionize the way we monitor and maintain restroom hygiene using IoT technologies. By combining hardware sensors, software applications, and cloud services, we've created a system that can detect various types of uncleanliness in restrooms and alert designated personnel in real-time. Our goal is to improve restroom cleanliness, reduce water wastage, and ultimately enhance public health.

## Key Features:
Automated Monitoring: Utilizing sensors such as the Nodemcu esp8266, Ultrasonic sensor, Mq-135 (odor sensor), and Water sensor, our system continuously monitors restroom conditions.
Real-time Alerts: Upon detecting issues like unpleasant odors, low water levels, or broken accessories, alerts are sent to designated personnel for immediate action.
User Feedback: A website form allows users to provide feedback and upload images of malfunctioning appliances, enabling quick identification and resolution.
Image Processing: Implemented the ORB algorithm to detect broken objects from uploaded images, helping authorities prioritize maintenance tasks.
Cloud Integration: All data is stored in Firebase Realtime Database and Storage, enabling easy access and monitoring from anywhere.

## Impact:
Water Conservation: By promptly identifying leaks and inefficiencies, our system has led to a 70% reduction in water wastage.
Public Health: Improved restroom cleanliness contributes to the prevention of infections and diseases, benefiting millions of individuals.

## Technologies Used:
Hardware: Nodemcu esp8266, Ultrasonic sensor, Mq-135 (odor sensor), Water sensor.
Software: C++, Python, HTML, CSS, JavaScript.
Cloud Services: Firebase Realtime Database and Storage.
Integration: Twilio for SMS notifications.
