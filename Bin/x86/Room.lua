Room = {}

-- Simply a class which stores the name of a room.

function Room:new(r_name)    
    local room = { name = r_name }
    
    function room:GetRoomName()
        return self.name
    end
    
    return room
end
