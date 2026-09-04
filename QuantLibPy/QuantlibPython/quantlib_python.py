"""Test Object Handler based Python exports of QuantlibXL."""

import os
import sys
from distutils.dir_util import copy_tree
from time import perf_counter

# get an absolute hook to express relative positions
script_fld = os.path.dirname(os.path.realpath(__file__))

# get build configuration from environment variables
target_type = os.environ.get('PDG_TARGET_TYPE', 'Release')
address_mdl = os.environ.get('PDG_ADDRESS_MODEL', 'x64')
x_mdl = 'x86' if address_mdl == 'x86' else 'x64'

third_pyt_root = os.environ.get('THIRD_PTY_ROOT', 'THIRD_PTY_ROOT not defined')
oh_fld = third_pyt_root + r"\quantlib\ObjectHandler\ohpy\OhPython\build\x64\Release"
module_fld = os.path.join(script_fld, 'build', x_mdl, target_type)

# 1. Aggiungi i percorsi a sys.path per la ricerca dei moduli Python/PYD
for fld in [oh_fld, module_fld]:
    if fld not in sys.path:
        sys.path.insert(0, fld)

# 2. Aggiungi i percorsi in modo PERMANENTE per il caricamento delle DLL di Windows
_dll_handles = []
if hasattr(os, 'add_dll_directory'):
    if os.path.exists(oh_fld):
        _dll_handles.append(os.add_dll_directory(oh_fld))
    if os.path.exists(module_fld):
        _dll_handles.append(os.add_dll_directory(module_fld))

# 3. Importa i moduli in ordine
try:
    import py_oh
    print("LOG: 'py_oh' caricato con successo.")
except Exception as e:
    print(f"ERRORE caricamento py_oh: {e}")

try:
    import py_quantlib
    print("LOG: 'py_quantlib' caricato con successo.")
except Exception as e:
    print(f"ERRORE caricamento py_quantlib: {e}")

#help(py_quantlib)
#help(py_quantlib.qlSchedule)

def testFunction():
    a = py_quantlib.qlSettingsEvaluationDate()
    print(f"EvaluationDate = {a}")
    py_quantlib.qlSettingsSetEvaluationDate(a+30)
    b = py_quantlib.qlSettingsEvaluationDate()
    print(f"Shifted EvaluationDate = {b}")

    effectiveDate = b
    terminationDate= b +3600
    tenor = "1Y"
    calendar = "NullCalendar"
    convention = "Unadjusted"
    termDateConv = "Unadjusted"
    genRule="Backward"
    endOfMonth = False
    firstDate = None
    nextToLastDate = None
    c = py_quantlib.qlSchedule("sheduleId", effectiveDate, terminationDate, tenor, calendar, convention, termDateConv, genRule, endOfMonth, firstDate, nextToLastDate, True)
    print(c)
    d = py_quantlib.qlScheduleEndDate(c)
    print(f"ScheduleEndDate = {d}")
    e = py_quantlib.qlCalendarAdjust("TARGET",[d],"Following")
    print(f"Adjusted scheduleEndDate = {e}")
    f = py_oh.ohRepositoryListObjectIDs("")
    print(f)
    py_oh.ohObjectSave(f, "prova.xml", True, None)

def main():
    """main function"""
    name = 'PyQuantlib function examples'
    print('===========================================')
    try:
        start = perf_counter()
        testFunction()
        duration = perf_counter() - start
        print('{} took {:.3f} seconds\n'.format(name, duration))
    except py_oh.PyOH_error as err:
        print("error:" + str(err)) #py_quantlib.error_out()#

if __name__ == "__main__":
    main()
