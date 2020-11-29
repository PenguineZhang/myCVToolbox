import numpy as np
import matplotlib.pyplot as plt
import scipy.signal
import cv2
import time

class CornerDetection(object):
    def __init__(self):
        pass

    def corners(self, img: np.ndarray, kernel: np.ndarray, algorithm='harris', w='box'):
        '''
        input: img - grayscale image needed to find corners
               algorithm - ['harris', 'forstner']
               w : Weighting matrix for gradient image, available: ['gaussian', 'box']. Default is 'box' matrix
        '''
        if len(img.shape) > 2:
            raise NotGrayscaleImageError()

        available_w = ['box', 'gaussian']

        filter = None
        if w in available_w:
            if w == 'box':
                filter = self.box2dGeneration()
            elif w == 'gaussian':
                filter = self.gaussian2dGeneration()
        else:
            raise Exception("Filter option unavailable")

        # kernel for I_x
        kernel_x = np.expand_dims(kernel.flatten(), 0)

        # kernel for I_y
        kernel_y = np.transpose(kernel_x)

        # calculate gradient map in X direction
        I_x = scipy.signal.convolve2d(img, kernel_x, mode="same")

        # calculate gradient map in Y direction
        I_y = scipy.signal.convolve2d(img, kernel_y, mode="same")

        # precompute I_x^2, I_y^2, I_x*I_y
        I_x2 = I_x**2
        I_y2 = I_y**2
        I_xy = I_x*I_y

        filter_size = filter.shape
        h, w = img.shape

        row_start = filter_size[0]//2
        row_end = h - filter_size[0]//2
        col_start = filter_size[1]//2
        col_end = h - filter_size[1]//2

        epsilon = 1e-1
        corners = np.zeros((row_end - row_start, col_end - col_start))
        t = time.time()
        A = np.zeros((2,2))
        if algorithm == "harris":
            # TODO: Too slow (10s to run), need to improve speed
            for i in range(row_start, row_end):
                for j in range(col_start, col_end):
                    A[0, 0] = np.sum(I_x2[i-filter_size[0]//2:i+filter_size[0]//2+1, j-filter_size[1]//2:j+filter_size[1]//2+1]) / kernel.size**2
                    A[1, 1] = np.sum(I_y2[i-filter_size[0]//2:i+filter_size[0]//2+1, j-filter_size[1]//2:j+filter_size[1]//2+1]) / kernel.size**2
                    A[1, 0] = np.sum(I_xy[i-filter_size[0]//2:i+filter_size[0]//2+1, j-filter_size[1]//2:j+filter_size[1]//2+1]) / kernel.size**2
                    A[0, 1] = A[1, 0]
                    corners[i-1, j-1] = 2 * np.linalg.det(A) / (np.trace(A) + epsilon) / 255
        elif algorithm == "forstner":
            X, Y = np.meshgrid(range(row_end - row_start), range(col_end - col_start))
            for i in range(row_start, row_end):
                for j in range(col_start, col_end):
                    Ix2 = np.sum(I_x2[i-filter_size[0]//2:i+filter_size[0]//2+1, j-filter_size[1]//2:j+filter_size[1]//2+1] * filter)
                    Iy2 = np.sum(I_y2[i-filter_size[0]//2:i+filter_size[0]//2+1, j-filter_size[1]//2:j+filter_size[1]//2+1] * filter)
                    Ixy = np.sum(I_xy[i-filter_size[0]//2:i+filter_size[0]//2+1, j-filter_size[1]//2:j+filter_size[1]//2+1] * filter)
                    A = np.array([[Ix2, Ixy], [Ixy, Iy2]])
        
        print(time.time() - t)
        cv2.imshow("corner", corners)
        cv2.waitKey(0)

        return 1
    
    def harrisCornerDetector(self, filter):
        pass


    def matchCorners(self, image1, image2):
        pass


    @staticmethod
    def gaussian2dGeneration(dim=[3,3]):

        if len(dim) > 2:
            # TODO: make this an exception
            print("Dimension must be 2d")

        if dim[0] != dim[1]:
            # TODO: make this an exception
            print("Must be square matrix")

        sigma_x = 1
        sigma_y = 1
        theta = 0

        X, Y = np.meshgrid(range(-dim[0], dim[0]+1), range(-dim[0], dim[0]+1))

        A = 1
        a = np.cos(theta)**2 / (2 * sigma_x**2) + np.sin(theta)**2 / (2 * sigma_y**2)
        b = -np.sin(2 * theta) / (4 * sigma_x**2) + np.sin(2 * theta) / (4 * sigma_y**2)
        c = np.sin(theta)**2 / (2 * sigma_x**2) + np.cos(theta)**2 / (2 * sigma_y**2)

        return A * np.exp( -(a * X**2 + 2 * b * X * Y + c * Y**2))

    @staticmethod
    def box2dGeneration(dim=[3,3]):

        if len(dim) > 2:
            # TODO: make this an exception.
            print("Dimension must be 2d")

        if dim[0] != dim[1]:
            # TODO: make this an exception
            print("Must be square matrix")

        h, w = dim[0], dim[1]
        box_filter = 1 / (h*w) * np.ones((h, w))
        return box_filter


def main():
    img = cv2.imread("test.png", 0)
    kernel = 1/12 * np.array([[-1, 8, 0, -8, 1]])
    corner_detector = CornerDetection()
    corners = corner_detector.corners(img, kernel=kernel)


if __name__ == '__main__':
    main()