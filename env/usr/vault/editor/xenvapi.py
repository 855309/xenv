import pathlib
import os

def joinpath(path1: str, path2: str):
    if path2 == "..":
        sonp = ""
        splp = path1.split("/")
        splp.pop()
        for s in splp:
            sonp += s + "/"
        if len(sonp) != 1:
            sonp = sonp[:-1]
        return sonp
    elif path2 == ".":
        return path1
    else:
        newp = ""
        b1 = False
        f2 = False
        if path1[-1] == "/":
            b1 = True
        
        if path2[0] == "/":
            f2 = True

        if b1:
            newp += path1
            newp = newp[:-1]
        else:
            newp += path1
        
        newp += "/"

        if f2:
            newp += path2[1:]
        else:
            newp += path2
        
        return newp

def getappdir():
    currentusr = pathlib.Path(__file__).parent
    fp = str(currentusr.absolute())
    typ = fp.split("/")[-1]
    if typ == "bin": # build/env/usr/bin
        return joinpath(joinpath(joinpath(fp, ".."), ".."), "..")
    elif joinpath(fp, "..").split("/")[-1] == "vault": # build/env/usr/vault/app
        return joinpath(joinpath(joinpath(joinpath(fp, ".."), ".."), ".."), "..")
    else:
        return "error."

def getfspath():
    return joinpath(getappdir(), "env/")

def getrealpath(pathinfs: str):
    return joinpath(getfspath(), pathinfs[1:])

def getcurrentpath():
    with open(getrealpath("/etc/session/0"), "r") as rx:
        pth = rx.read().strip()
        return pth
