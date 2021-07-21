import cv2 as cv
import numpy as np

p = r"a59d47ad-3cdc-4e5c-a982-834fe39ecfdf.jpg"
img = cv.imread(p)
imgGray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)

b, g, r = cv.split(img);

imgBlur  = cv.GaussianBlur(imgGray, (7, 7), 1);
imgCanny = cv.Canny(imgBlur, 100, 150);

hmin, smin, vmin = 0, 0, 0
hmax, smax, vmax = 179, 255, 255

def callback(x):
	# global hmin, hmax, smin, smax, vmin, vmax
    global hmin, hmax, smin, smax, vmin, vmax
    hmin  = cv.getTrackbarPos('hmin', 'trackbar')
    hmax  = cv.getTrackbarPos('hmax', 'trackbar')
    smin  = cv.getTrackbarPos('smin', 'trackbar')
    smax  = cv.getTrackbarPos('smax', 'trackbar')
    vmin  = cv.getTrackbarPos('vmin', 'trackbar')
    vmax  = cv.getTrackbarPos('vmax', 'trackbar')

win = cv.namedWindow("trackbar")
cv.createTrackbar("hmin", "trackbar", 0, 179, callback);
cv.createTrackbar("hmax", "trackbar", 179, 179, callback);

cv.createTrackbar("smin", "trackbar", 0, 255, callback);
cv.createTrackbar("smax", "trackbar", 255, 255, callback);

cv.createTrackbar("vmin", "trackbar", 0, 255, callback);
cv.createTrackbar("vmax", "trackbar", 255, 255, callback);

w, h, _ = img.shape
asp_ratio = w / h * 0.5

while True:
    # get trackbar positions
    hmin  = cv.getTrackbarPos('hmin', 'trackbar')
    hmax  = cv.getTrackbarPos('hmax', 'trackbar')
    smin  = cv.getTrackbarPos('smin', 'trackbar')
    smax  = cv.getTrackbarPos('smax', 'trackbar')
    vmin  = cv.getTrackbarPos('vmin', 'trackbar')
    vmax  = cv.getTrackbarPos('vmax', 'trackbar')

    min_hsv = np.array([hmin, smin, vmin], np.uint8)
    max_hsv = np.array([hmax, hmax, vmax], np.uint8)

    img = cv.imread(p)
    imgResize = cv.resize(img, (0,0), fx=asp_ratio, fy=asp_ratio)
    imgHSV    = cv.cvtColor(imgResize, cv.COLOR_BGR2HSV)

    mask  = cv.inRange(imgHSV, min_hsv, max_hsv)
    frame = cv.bitwise_and(imgResize, imgResize, mask=mask)
    cv.imshow('frame', frame)
    # cv.imshow('hsv', imgHSV)
    # cv.imshow("hsv", imgResize)
    k = cv.waitKey(1) & 0xFF
    if k == 27:
        break

# cv.imshow("gray", imgBlur)
# cv.imshow("canny", imgCanny)
# cv.imshow("r", r);

# cv.waitKey(0)
cv.destroyAllWindows()