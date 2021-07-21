import cv2
import pytesseract

pytesseract.pytesseract.tesseract_cmd = r'E:\Program\Tesseract-OCR64\tesseract.exe'

path = r'C:\Users\Aurora_Boreas\Desktop\opencv_grandmaster\20210701 AX75_White\solution3\example.jpg'
img = cv2.imread(path)
# img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
blur = cv2.GaussianBlur(gray, (5, 5), 0)
thresh = cv2.adaptiveThreshold(blur,255,1,1,11,2)
print(pytesseract.image_to_boxes(thresh))

cv2.imshow('image', thresh)
cv2.waitKey(0)