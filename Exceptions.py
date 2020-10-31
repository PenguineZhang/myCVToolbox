class NotGrayscaleImageError(Exception):
    def __init__(self, message="Image must be a grayscale image"):
        self.message = message
        super().__init__(self.message)


class FilterUnavailableError(Exception):
    def __init__(self, message="Specified filter is unavailable"):
        self.message = message
        super().__init__(self.message)