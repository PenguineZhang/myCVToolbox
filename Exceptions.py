class NotGrayscaleImageError(Exception):
    def __init__(self, message="Image must be a grayscale image"):
        self.message = message
        super().__init__(self.message)