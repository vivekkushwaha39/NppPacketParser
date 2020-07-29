#!/usr/bin/python3
import io
import sys

from typing import Any, Iterable
from bertlv import config
from bertlv.parser import (
    BinaryParser,
    InsufficientDataError,
    ParserError,
    TreeBuilder,
    XmlParser,
    parse,
    parse_bytes,
)
from bertlv.tag import Tag
from bertlv.tree import TlvNode

def _TlvNode2Dict(tlvNode, dictData):
    children = tlvNode.children
    containerData = {}
    if len(children) == 0 :
        dictData["type"] = "leaf"
        dictData["tag"]=  tlvNode.name
        dictData["value"]= tlvNode.value.hex()
    else:
        for  i in children:
            containerData = {}
            _TlvNode2Dict(i, containerData)
    
    if len(children) != 0 :
        dictData[tlvNode.name] = containerData
        dictData["type"] = "parent"

def TlvNode2Dict(tlvTree):
    dictData = {}
    if tlvTree.is_root == True and len(tlvTree.children) >0 :
        _TlvNode2Dict(tlvTree, dictData)
    return dictData;

if len(sys.argv) != 2:
    exit(1)

byteString = sys.argv[1]

if len(byteString) <=0:
    exit (2)

bytes.fromhex(byteString)

fp = io.BytesIO(bytes.fromhex(byteString))
treedata = parse(fp, BinaryParser())
dictData = TlvNode2Dict(treedata)
print(dictData)