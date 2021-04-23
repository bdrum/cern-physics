from pandas import DataFrame

# TODO: in case of classes I can add _getattr__ and put validation there...


def IsDataFrame(tracks):
    if (type(tracks) != DataFrame):
        raise AttributeError('Input data should be a pandas DataFrame')
