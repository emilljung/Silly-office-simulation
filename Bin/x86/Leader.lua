function newLeader(baseClass)
    print(baseClass:GetName() .. ": 'Not these 2 guys again...'")

    local leader = { base = baseClass,
                     l_table = nil }
    
    function leader:getParent()
        return self.base
    end
    
    function leader:setEmployeeTable(table)
        self.l_table = table
    end

    function leader:update()        
        if self.base:GetRoom():GetRoomName() == "Office1" then
            if leader:inOffice() then
                leader:getParent():MoveTo(self.base:GetRoomTable()[4]) -- Till Corridor
            end
        else            
            if leader:inCorridor() then
                leader:getParent():MoveTo(self.base:GetRoomTable()[1]) -- Till Office1
            end         
        end
    end
    
    function leader:inOffice()
        move = false
        
        if self.l_table[3]:getParent():GetRoom():GetRoomName() ~= "Corridor" then
            print(leader:getParent():GetName() .. ": 'Nice, it's calm and work is going well!'")
        else
            print(leader:getParent():GetName() .. ": 'Huh? Who's walking around in the Corridor? I better check this...'")
            move = true
        end
        
        return move
    end
    
    function leader:inCorridor()
        if self.l_table[2]:getParent():GetRoom():GetRoomName() == "Corridor" then
            print(leader:getParent():GetName() .. ": '" .. self.l_table[2]:getParent():GetName() .. "! Are you trying to sneak out of here?! Get back to work!'")
            print(self.l_table[2]:getParent():GetName() .. ": 'Alright...'")
            
            self.l_table[2]:getParent():MoveTo(self.base:GetRoomTable()[2]) -- Rager går till Office 2
        else
            print(leader:getParent():GetName() .. ": 'I thought I heard something coming from here... Back to work!'")
        end
        
        return true -- Leader går alltid tillbaka till Office1 efter detta
    end

    return leader
end 