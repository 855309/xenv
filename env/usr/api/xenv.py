import pathlib
import os

def getenvpath():
    return pathlib.Path(os.path.join(pathlib.Path(__file__).parent, "..", "..")).absolute()

def getrealpath(fspath: str):
    return os.path.abspath(os.path.join(getenvpath(), fspath[1:]))