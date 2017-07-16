function newRager(baseClass, rage)
    print(baseClass:GetName() .. ": 'Phu, I'm actually quite calm today!'")
    
    local rager = { base = baseClass,
                    rageMeter = rage }

    function rager:getParent()
        return self.base
    end

    function rager:update()
        if self.base:GetRoom():GetRoomName() == "Office2" then
            if rager:inOffice() then
                rager:getParent():MoveTo(self.base:GetRoomTable()[4]) -- Till Corridor
            end
        else            
            if rager:inCorridor() then
                rager:getParent():MoveTo(self.base:GetRoomTable()[2]) -- Till Office2
            end         
        end
    end
    
    function rager:inOffice()
        move = false    -- Stanna i Office2
        val = math.random(-1,1)
        
        if val == 1 then
            -- Blir mer förbannad
            self.rageMeter = self.rageMeter + 1
            if self.rageMeter == 1 then
                print(rager:getParent():GetName() .. ": 'This is more difficult than I expected...' ")
            elseif self.rageMeter == 2 then
                print(rager:getParent():GetName() .. ": 'Grrr...' ")
            else
                print(rager:getParent():GetName() .. ": 'Fuck this shit!' ")
                move = true   -- Gå till Corridor
            end
        elseif val == -1 then
            -- Blir lugnare
            if self.rageMeter > 0 then
                self.rageMeter = self.rageMeter - 1
                if self.rageMeter == 2 then
                    print(rager:getParent():GetName() .. ": 'Ok... try to calm down...' ")
                elseif self.rageMeter == 1 then
                    print(rager:getParent():GetName() .. ": 'Hmm... ' ")
                else
                    print(rager:getParent():GetName() .. ": 'It works! Good thing I'm so calm :)' ")
            end
            else
                -- Försöker bli lugnare än 0
                print(rager:getParent():GetName() .. ": 'I'm so calm I could fall asleep!' ")
            end
        else
            -- Oförändrad ilska, val == 0
            print(rager:getParent():GetName() .. ": 'This is so annoying...' ")
        end
        
        return move
    end
    
    function rager:inCorridor()
        move = false  -- Stanna kvar i Corridor
        
        if self.rageMeter > 0 then
            self.rageMeter = self.rageMeter - 1
            print(rager:getParent():GetName() .. ": 'Calm down " .. rager:getParent():GetName() .. "... Calm down...' ")
        else
            print(rager:getParent():GetName() .. ": 'Time to go back to my office!' ")
            move = true -- Gå till Office2        
        end
        
        return move
    end

    return rager
end 