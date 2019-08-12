
"""
 Copyright (C) 2019 Giorgio Facchinetti
 FOR A PARTICULAR PURPOSE.  See the license for more details.
"""

"""Generate source code for Python addin."""

from gensrc.addins import addin
from gensrc.addins import cppexceptions
from gensrc.configuration import environment
from gensrc.categories import category
from gensrc.utilities import outputfile
from gensrc.utilities import log
from gensrc.utilities import common

class PythonAddin(addin.Addin):
    """Generate source code for Python addin."""

    #############################################
    # class variables
    #############################################
    prefix_ = ''

    #############################################
    # public interface
    #############################################

    def generate(self, categoryList, enumerationList):
        """Generate source code for Python addin."""
            
        self.categoryList_ = categoryList
        self.enumerationList_ = enumerationList

        log.Log.instance().logMessage(' begin generating %s...' % self.name_)
        self.generateFunctions()
        self.generateDef()
        log.Log.instance().logMessage(' done generating %s.' % self.name_)

    def generateFunctions(self):
        """Generate source code for all functions in all categories."""
        for cat in self.categoryList_.categories(self.name_, self.coreCategories_, self.addinCategories_):
            categoryIncludes = cat.includeList()
            bufferCpp = ''
            bufferHpp = ''
            for func in cat.functions(self.name_): 
                bufferCpp += self.generateFunction(func)
                bufferHpp += self.generateDeclaration(func)
            self.bufferBody_.set({
                'bufferCpp' : bufferCpp,
                'namespaceObjects' : environment.config().namespaceObjects(),
                'categoryIncludes' : categoryIncludes,
                'categoryName' : cat.name() })
            self.bufferHeader_.set({
                'categoryName' : cat.name(),
                'namespaceObjects' : environment.config().namespaceObjects(),
                'bufferHpp' : bufferHpp })
            fileNameCpp = '%spydg_%s.cpp' % ( self.rootPath_, cat.name())
            outputfile.OutputFile(self, fileNameCpp, self.copyright_, self.bufferBody_)
            fileNameHpp = '%spydg_%s.hpp' % ( self.rootPath_, cat.name())
            outputfile.OutputFile(self, fileNameHpp, self.copyright_, self.bufferHeader_)
        
              
    def generateDef(self):
        """"""
        defSymbols = ''
        includeFiles = ''
        for cat in self.categoryList_.categories(self.name_, self.coreCategories_, self.addinCategories_):
            includeFiles += '\n#include \"pydg_' + cat.name() + '.hpp\"'
            for func in cat.functions(self.name_):
                defSymbols += '\n\t{ "'+ func.name() + '", (PyCFunction)PdgLibAddinPy::'+ func.name() + ', METH_VARARGS, "Arguments(' + self.generateArgsDescription(func, self.argsDescription_)+ ')"},' 
        
        self.defStub_.set({'includeFiles' : includeFiles,
                           'defSymbols' : defSymbols,
                           'prefix' : self.prefix_})
        fileName = self.rootPath_ + '/pydg_defines.hpp'
        outputfile.OutputFile(self, fileName, None, self.defStub_)
        
    def generateArgsDescription(self, func, ruleGroup):
        """Generate arguments description"""        
        codeItems = []
        for param in func.parameterList().parameters_:
            ruleResult = ruleGroup.apply(param)
            if ruleResult and not(param.ignore_):
                codeItems.append("\\n\\t " + ruleResult)
        code = ruleGroup.delimiter().join(codeItems)
        return code

    def generateFunction(self, func):
        """Generate source code for a given function."""
        return self.bufferFunction_.set({
            'cppConversions' : func.parameterList().generate(self.cppConversions_),
            'enumConversions' : func.parameterList().generate(self.enumConversions_),
            'functionBody' : func.generateBody(self),
            'functionName' : func.name(),
            'libConversions' : func.parameterList().generate(self.libraryConversions_),
            'objectConversions' : func.parameterList().generate(self.objectConversions_),
            'refConversions' : func.parameterList().generate(self.referenceConversions_),
            'returnConversion' : self.returnConversion_.apply(func.returnValue()),
            'nArgs' : func.parameterList().parametersSize()})

    def generateDeclaration(self, func):
        """Generate source code for a given function."""
        return self.bufferDeclaration_.set({
            'functionName' : func.name() })

    #############################################
    # serializer interface
    #############################################

    def serialize(self, serializer):
        """Load/unload class state to/from serializer object."""
        super(PythonAddin, self).serialize(serializer)
        serializer.serializeProperty(self, 'prefix')

