import pyrebase
from twilio.rest import Client
import requests
import glob
import os
import cv2

firebaseConfig1 = {
    "apiKey": "AIzaSyDqJk-6ulRqdYozYeUVxdppM6CpDS_76bY",
    "authDomain": "feedbackform-iot.firebaseapp.com",
    "databaseURL": "https://feedbackform-iot-default-rtdb.firebaseio.com/",
    "projectId": "feedbackform-iot",
    "storageBucket": "feedbackform-iot.appspot.com",
    "messagingSenderId": "448782781174",
    "appId": "1:448782781174:web:789850e6382d03017a3ad7",
}

firebaseConfig2 = {
    "apiKey": "AIzaSyDBl27n1Ujn8lFOewEyL-TFK3MeKhhJC-Y",
    "authDomain": "ultrasonic-sensor-98d22.firebaseapp.com",
    "databaseURL": "https://ultrasonic-sensor-98d22-default-rtdb.firebaseio.com",
    "projectId": "ultrasonic-sensor-98d22",
    "storageBucket": "ultrasonic-sensor-98d22.appspot.com",
    "messagingSenderId": "905291245752",
    "appId": "1:905291245752:web:0c34cf1664a417f507ac4d",
}

firebase_form = pyrebase.initialize_app(firebaseConfig1)
firebase_sensor = pyrebase.initialize_app(firebaseConfig2)
database_form = firebase_form.database()
database_sensor = firebase_sensor.database()

form_res = database_form.child("feedbackForm-IOT").get()
distance_res = database_sensor.child("Distance").get()
distance_res1 = database_sensor.child("Distance1").get()
gas_res = database_sensor.child("Gas_Value").get()
water_res = database_sensor.child("Value").get()
water_res1 = database_sensor.child("Value1").get()
water_res2 = database_sensor.child("Value2").get()
water_res3 = database_sensor.child("Value3").get()
img_url = database_form.child("Image-URL").get()
# print(form_res.val())
# print(distance_res.val())
# print(gas_res.val())
# print(water_res.val())
form_res_odour = []
form_res_avail = []
form_res_avail1 = []
form_res_leak = []
form_res_leak1 = []
form_res_leak2 = []
form_res_leak3 = []
img_url_list = []

for i in form_res.each():
    x = i.val()['odour']
    y = i.val()['wateravail']
    z = i.val()['waterleak']
    form_res_odour.append(x)
    form_res_avail.append(y)
    form_res_leak.append(z)

for i in distance_res.each():
    a = i.val()

for i in distance_res1.each():
    a1 = i.val()

for i in gas_res.each():
    b = i.val()

for i in water_res.each():
    c = i.val()

for i in water_res1.each():
    c1 = i.val()

for i in water_res2.each():
    c2 = i.val()

for i in water_res3.each():
    c3 = i.val()

account_sid = 'ACaa42fe1a0ed9666ebe1148f5e38762cb'
auth_token = 'b9d0bf3236e6aa413dd977df670ac42f'
twilio_number = '+18596966359'
target_number = '+917506989551'

client = Client(account_sid, auth_token)

if form_res_avail[-1] == "no" and a < 100:
    message1 = client.messages.create(
        body="The water in tank is low. Please refill the tank/टंकी में पानी कम है। कृपया टैंक को फिर से भरें ",
        from_=twilio_number,
        to=target_number,
    )
if form_res_odour[-1] == "yes" and b > 300:
    message2 = client.messages.create(
        body="There is foul odour in the toilet/शौचालय में दुर्गंध आ रही है",
        from_=twilio_number,
        to=target_number,
    )
if form_res_leak[-1] == "yes" and c == 1 or c1 == 1 or c2 == 1 or c3 == 1:
    message3 = client.messages.create(
        body="The bathroom floor is flooded with water please take care of situation urgently/बाथरूम का फर्श पानी से भर गया है कृपया स्थिति पर तत्काल ध्यान दें",
        from_=twilio_number,
        to=target_number,
    )


def orb_sim(img1, img2):
    # SIFT is no longer available in cv2 so using ORB
    orb = cv2.ORB_create()

    # detect keypoints and descriptors
    kp_a, desc_a = orb.detectAndCompute(img1, None)
    kp_b, desc_b = orb.detectAndCompute(img2, None)

    # define the bruteforce matcher object
    bf = cv2.BFMatcher(cv2.NORM_HAMMING, crossCheck=True)

    # perform matches.
    matches = bf.match(desc_a, desc_b)
    # Look for similar regions with distance < 50. Goes from 0 to 100 so pick a number between.
    similar_regions = [i for i in matches if i.distance < 50]
    if len(matches) == 0:
        return 0
    return len(similar_regions) / len(matches)


for i in img_url.each():
    a = i.val()['url']
    img_url_list.append(a)

removing_files = glob.glob('D:\Code\Final Year Project\pic1.jpg')
for i in removing_files:
    os.remove(i)

with open('pic1.jpg', 'wb') as handle:
    response = requests.get(img_url_list[-1], stream=True)

    if not response.ok:
        print(response)

    for block in response.iter_content(1024):
        if not block:
            break

        handle.write(block)

proper_tap_img = cv2.imread('tap.jpg', 0)
proper_toilet_seat = cv2.imread('toilet_seat.jpg', 0)
proper_mirror = cv2.imread('mirror.jpg', 0)
img01 = cv2.imread('pic1.jpg', 0)

orb_similarity_tap = orb_sim(proper_tap_img, img01)
orb_similarity_toilet_seat = orb_sim(proper_toilet_seat, img01)
orb_similarity_mirror = orb_sim(proper_mirror, img01)

# print("Similarity using ORB is: ", orb_similarity_toilet_seat)
# print("Similarity using ORB is: ", orb_similarity_tap)
# print("Similarity using ORB is: ", orb_similarity_mirror)

if 0.25 < orb_similarity_tap < 0.80:
    message4 = client.messages.create(
        body="The Tap in the washroom is broken/वॉशरूम में नल टूटा हुआ है",
        from_=twilio_number,
        to=target_number,
    )
if 0.3 < orb_similarity_toilet_seat < 0.80:
    message5 = client.messages.create(
        body="The Toilet Seat is Broken/ टॉयलेट सीट टूटी हुई है",
        from_=twilio_number,
        to=target_number,
    )
if 0.3 < orb_similarity_mirror < 0.85:
    message6 = client.messages.create(
        body="The Mirror in Washroom is Broken/ वॉशरूम का शीशा टूटा हुआ है",
        from_=twilio_number,
        to=target_number,
    )
