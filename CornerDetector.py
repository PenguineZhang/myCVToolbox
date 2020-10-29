#!/home/peng/anaconda3/envs/fcnd/bin/python

from Exceptions import *
import numpy as np
import cv2

class CornerDetection(object):
    def __init__(self):
        pass

    def corners(self, img: np.ndarray, algorithm='harris'):
        '''
        input: img - grayscale image needed to find corners
               algorithm - ['harris', 'forstner']
        '''
        if len(img.shape) > 2:
            raise NotGrayscaleImageError()


        return 1

    def matchCorners(self, image1, image2):
        pass

corner_detector = CornerDetection()
fake_data = np.random.randn(30,30,3)
corners = corner_detector.corners(fake_data)