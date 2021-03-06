"""
The DoInterestManager keeps track of which parent/zones that we currently
have interest in.  When you want to "look" into a zone you add an interest
to that zone.  When you want to get rid of, or ignore, the objects in that
zone, remove interest in that zone.

p.s. A great deal of this code is just code moved from ClientRepository.py.
"""

from pandac.PandaModules import *
from MsgTypes import *
from direct.directnotify import DirectNotifyGlobal
from direct.showbase.PythonUtil import *
from direct.showbase import DirectObject
from PyDatagram import PyDatagram
#from PyDatagramIterator import PyDatagramIterator


class DoInterestManager(DirectObject.DirectObject):
    """
    Top level Interest Manager
    """
    if __debug__:
        notify = DirectNotifyGlobal.directNotify.newCategory("DoInterestManager")
        
        
    _interestIdAssign = 1;
    _interestIdScopes = 100;
    _interests = {}
        

    def __init__(self):
        assert self.notify.debugCall()
        DirectObject.DirectObject.__init__(self)

    def addInterest(self, parentId, zoneIdList, description, event=None):
        """
        Look into a zone.
        """
        assert self.notify.debugCall()
        DoInterestManager._interestIdAssign += 1
        DoInterestManager._interestIdScopes  += 1
        contextId = DoInterestManager._interestIdAssign
        scopeId = DoInterestManager._interestIdScopes
        DoInterestManager._interests[contextId] = [description, scopeId, event, "Active"]
        self._sendAddInterest(contextId, scopeId, parentId, zoneIdList)
        assert self.printInterests()
        return contextId

    def removeInterest(self,  contextId, event=None):
        """
        Stop looking in a zone
        """
        assert self.notify.debugCall()
        answer = 0
        if  DoInterestManager._interests.has_key(contextId):
            if event is not None:
                DoInterestManager._interestIdScopes  += 1
                DoInterestManager._interests[contextId][3] = "PendingDel"
                DoInterestManager._interests[contextId][2] = event
                DoInterestManager._interests[contextId][1] = DoInterestManager._interestIdScopes
                self._sendRemoveInterest(contextId)
            else:
                DoInterestManager._interests[contextId][2] = None
                DoInterestManager._interests[contextId][1] = 0
                self._sendRemoveInterest(contextId)
                del DoInterestManager._interests[contextId]
            answer = 1
        else:
            self.notify.warning("removeInterest: contextId not found: %s" % (contextId))
        assert self.printInterests()
        return answer

    def alterInterest(self, contextId, parentId, zoneIdList, description=None, event=None):
        """
        Removes old interests and adds new interests.
        """
        assert self.notify.debugCall()
        answer = 0
        if  DoInterestManager._interests.has_key(contextId):
            DoInterestManager._interestIdScopes  += 1
            if description is not None:
                DoInterestManager._interests[contextId][0] = description

            DoInterestManager._interests[contextId][1] = DoInterestManager._interestIdScopes;
            DoInterestManager._interests[contextId][2] = event;
            self._sendAddInterest(contextId, DoInterestManager._interestIdScopes, parentId, zoneIdList)
            answer = 1
            assert self.printInterests()
        else:
            self.notify.warning("alterInterest: contextId not found: %s" % (contextId))
        return answer


    def getInterestScopeId(self, contextId):
        """
        Part of the new otp-server code.
             Return a ScopeId Id for an Interest
        """
        assert self.notify.debugCall()
        answer = 0
        if  DoInterestManager._interests.has_key(contextId):
            answer = DoInterestManager._interests[contextId][1];
        else:
            self.notify.warning("GetInterestScopeID: contextId not found: %s" % (contextId))
        return answer


    def getInterestScopeEvent(self, contextId):
        """
        returns an event for an interest.
        """
        assert self.notify.debugCall()
        answer = None
        if  DoInterestManager._interests.has_key(contextId):
            answer = DoInterestManager._interests[contextId][2];
        else:
            self.notify.warning("GetInterestScopeEvent: contextId not found: %s" % (contextId))
        return answer

    def _ponderRemoveFlaggedInterest(self, handle):
        """
        Consider whether we should cull the interest set.
        """
        assert self.notify.debugCall()
        if  DoInterestManager._interests.has_key(handle):
                if DoInterestManager._interests[handle][3] == "PendingDel":
                    del DoInterestManager._interests[handle]

    if __debug__:
        def printInterests(self):
            """
            Part of the new otp-server code.
            """
            print "*********************** Interest Sets **************"
            for i in DoInterestManager._interests.keys():
                 print "Interest ID:%s, Description=%s Scope=%s Event=%s Mode=%s"%(
                     i,
                     DoInterestManager._interests[i][0],
                     DoInterestManager._interests[i][1],
                     DoInterestManager._interests[i][2],
                     DoInterestManager._interests[i][3])
            print "****************************************************"
            return 1 # for assert()

    def _sendAddInterest(self, contextId, scopeId, parentId, zoneIdList):
        """
        Part of the new otp-server code.

        contextId is a client-side created number that refers to
                a set of interests.  The same contextId number doesn't
                necessarily have any relationship to the same contextId
                on another client.
        """
        assert self.notify.debugCall()
        datagram = PyDatagram()
        # Add message type
        datagram.addUint16(CLIENT_ADD_INTEREST)
        datagram.addUint16(contextId)
        datagram.addUint32(scopeId)
        datagram.addUint32(parentId)
        if isinstance(zoneIdList, types.ListType):
            vzl = list(zoneIdList)
            vzl.sort()
            PythonUtil.uniqueElements(vzl)
            for zone in vzl:
                datagram.addUint32(zone)
        else:
           datagram.addUint32(zoneIdList)
        self.send(datagram)

    def _sendRemoveInterest(self, contextId):
        """
        contextId is a client-side created number that refers to
                a set of interests.  The same contextId number doesn't
                necessarily have any relationship to the same contextId
                on another client.
        """
        assert self.notify.debugCall()
        datagram = PyDatagram()
        # Add message type
        datagram.addUint16(CLIENT_REMOVE_INTEREST)
        datagram.addUint16(contextId)
        self.send(datagram)

    def handleInterestDoneMessage(self, di):
        """
        This handles the interest done messages and may dispatch a
        action based on the ID, Context
        """
        assert self.notify.debugCall()
        id = di.getUint16()
        scope = di.getUint32()
        expect_scope = self.getInterestScopeId(id)
        print "handleInterestDoneMessage--> Received ID:%s Scope:%s"%(id,scope);
        if expect_scope == scope:
            print "handleInterestDoneMessage--> Scope Match:%s Scope:%s"%(id,scope);
            event = self.getInterestScopeEvent(id)
            if event is not None:
                print "handleInterestDoneMessage--> Send Event : %s"%(event);
                messenger.send(event)
            else:
                print "handleInterestDoneMessage--> No Event ";
            self._ponderRemoveFlaggedInterest(id)
        else:
            print "handleInterestDoneMessage--> Scope MisMatch :%s :%s"%(expect_scope,scope);

        assert self.printInterests()

