
"""
 Copyright (C) 2005, 2006, 2007 Eric Ehlers

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
"""

"""Represent a file which gets overwritten only when its contents change."""

from gensrc.configuration import environment
from gensrc.utilities import log
import os
import sys
import filecmp
import re

class OutputFile(object):
    """Represent a file which gets overwritten only when its contents change."""

    #############################################
    # class variables
    #############################################
    
    TRIM_WHITESPACE = re.compile(r'^ *', re.M)
    HEADER = """\
%(comment)s This file was generated automatically by %(filename)s.  If you edit this file
%(comment)s manually then your changes will be lost the next time gensrc runs.\n\n"""
    UPDATE_MSG = '%-100s %10s'
    STUBFILE_NAME = """\
%(comment)s This source code file was generated from the following stub:
%(comment)s      %(filename)s\n\n"""


    #############################################
    # public interface
    #############################################

    def printCopyright(self, copyright):
        """Print the copyright message relevant for this source code file."""
        copyrightTrim = OutputFile.TRIM_WHITESPACE.sub(' ', copyright)
        self.outFile_.write(environment.config().copyrightBuffer() % 
            { 'copyright' : copyrightTrim } )

    def printHeader(self, commentPrefix):
        """Print the gensrc comment header for this source code file."""
        self.outFile_.write(OutputFile.HEADER % {
            'filename' : os.path.basename(sys.argv[0]),
            'comment' : commentPrefix })

    def close(self):
        """Close temp file and overwrite original if they are different."""
        self.outFile_.close()
        if os.path.exists(self.fileName_):
            if filecmp.cmp(self.fileName_, self.fileNameTemp_):
                os.unlink(self.fileNameTemp_)
                log.Log.instance().logMessage(OutputFile.UPDATE_MSG %
                    (self.fileName_ + ':', 'unchanged'))
                self.addin_.incrementUnchanged()
            else:
                os.unlink(self.fileName_)
                os.rename(self.fileNameTemp_, self.fileName_)
                log.Log.instance().logMessage(OutputFile.UPDATE_MSG %
                    (self.fileName_ + ':', 'updated'))
                self.addin_.incrementUpdated()
        else:
            os.rename(self.fileNameTemp_, self.fileName_)
            log.Log.instance().logMessage(OutputFile.UPDATE_MSG %
                    (self.fileName_ + ':', 'created'))
            self.addin_.incrementCreated()

    #############################################
    # private member functions
    #############################################

    def __init__(self, addin, fileName, copyright, buffer, printHeader = True, commentPrefix = "//"):
        """Open file and write header."""
        self.addin_ = addin
        outPath = os.path.dirname(fileName)
        if not os.path.exists(outPath): os.makedirs(outPath)
        self.fileName_ = fileName
        self.fileNameTemp_ = self.fileName_ + '.temp'
        self.outFile_ = open(self.fileNameTemp_, 'w')
        if copyright:
            self.printCopyright(copyright)
        if printHeader:
            self.printHeader(commentPrefix)
        self.outFile_.write(OutputFile.STUBFILE_NAME % {
            'filename' : buffer.stubFileName(),
            'comment' : commentPrefix })
        self.outFile_.write(buffer.text())
        self.close()

