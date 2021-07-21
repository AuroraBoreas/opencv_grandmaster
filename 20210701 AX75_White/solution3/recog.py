import cv2
import pytesseract

pytesseract.pytesseract.tesseract_cmd = r'E:\Program\Tesseract-OCR64\tesseract.exe'

path = r'C:\Users\Aurora_Boreas\Desktop\opencv_grandmaster\20210701 AX75_White\solution3\example.jpg'
img = cv2.imread(path)
img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

## detect characters
# hImg, wImg, _ =  img.shape
# boxes = pytesseract.image_to_boxes(img)

# for box in boxes.splitlines():
#     print(box)
#     box = box.split(' ')
#     print(box)
#     x, y, w, h = int(box[1]), int(box[2]), int(box[3]), int(box[4])
#     cv2.rectangle(img, (x, hImg-y), (w, wImg-h), (0, 0, 255), 1)

## detect words
# hImg, wImg, _ =  img.shape
# boxes = pytesseract.image_to_data(img)
# print(boxes)
# for i, box in enumerate(boxes.splitlines()):
#     if i != 0:
#         box = box.split()
#         print(box)
#         if len(box)==12:
#             x, y, w, h = int(box[6]), int(box[7]), int(box[8]), int(box[9])
#             cv2.rectangle(img, (x, y), (x+w, h+y), (0, 0, 255), 1)

## detect digit numbers only
hImg, wImg, _ =  img.shape
conf = r'--oem 3 --psm 6 outputbase digits'
boxes = pytesseract.image_to_boxes(img, config=conf)
print(boxes)
for box in boxes.splitlines():
    print(box)
    box = box.split(' ')
    print(box)
    x, y, w, h = int(box[1]), int(box[2]), int(box[3]), int(box[4])
    cv2.rectangle(img, (x, hImg-y), (w, wImg-h), (0, 0, 255), 1)

cv2.imshow('image', img)
cv2.waitKey(0)