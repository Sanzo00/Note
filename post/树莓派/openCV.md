---

typora-copy-images-to: img

---

## 安装测试

```bash
sudo apt install libhdf5-dev libhdf5-serial-dev libqtgui4 libqtwebkit4 libqt4-test python3-pyqt5 libatlas-base-dev libjasper-dev

https://www.piwheels.org/simple/opencv-contrib-python/

sudo pip3 install opencv_contrib_python-4.4.0.46-cp37-cp37m-linux_armv7l.whl 
```

![image-20201208214701556](img/image-20201208214701556.png)



```python
# camTest.py

import cv2

cap = cv2.VideoCapture(0)
cap.set(3, 640)
cap.set(4, 480)

while True:
    ret, frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    cv2.imshow('frame', frame)
    cv2.imshow('gray', gray)

    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break

cap.release()
cv2.destroyAllWindows()
```



## 人脸检测

[haarcascade_frontalface_default.xml](https://github.com/opencv/opencv/blob/master/data/haarcascades/haarcascade_frontalface_default.xml)



```bash
# faceDection

import cv2

faceCascade = cv2.CascadeClassifier('Cascades/haarcascade_frontalface_default.xml')

cap = cv2.VideoCapture(0)
cap.set(3, 640)
cap.set(4, 480)

while True:
    ret, img = cap.read()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = faceCascade.detectMultiScale(
        gray,
        scaleFactor=1.2,
        minNeighbors=5,
        minSize=(20, 20)
    )

    for (x, y, w, h) in faces:
        cv2.rectangle(img, (x,y), (x+w, y+h), (255,0,0), 2)

    cv2.imshow('video', img)

    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break

cap.release()
cv2.destroyAllWindows()
```



## 收集数据

```python
# faceDataset.py

import cv2

faceCascade = cv2.CascadeClassifier('Cascades/haarcascade_frontalface_default.xml')

cap = cv2.VideoCapture(0)
cap.set(3, 640)
cap.set(4, 480)

face_id = input('enter user id:')
print("[INFO] Initializing face capture. Look the camera and wait...")
count = 0

while True:
    ret, img = cap.read()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = faceCascade.detectMultiScale(
        gray,
        scaleFactor=1.2,
        minNeighbors=5,
        #minSize=(20, 20)
    )

    for (x, y, w, h) in faces:
        cv2.rectangle(img, (x,y), (x+w, y+h), (255,0,0), 2)
        count += 1

        cv2.imwrite('dataset/User_{0}_{1}.jpg'.format(face_id, count), gray[y:y+h, x:x+w])
        cv2.imshow('image', img)

    k = cv2.waitKey(30) & 0xff
    if k == 27 or count >= 30:
        break

print('[INFO] Exiting Program and cleanup stuff.')
cap.release()
cv2.destroyAllWindows()
```

