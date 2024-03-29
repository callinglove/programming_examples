-- Dump RTP PCM payload to raw file
-- Write it to from<sourceIp_sourcePort>to<dstIp_dstPort> file.
-- You can access this feature by menu "Tools"
-- Author: Yang Xing (hongch_911@126.com)
------------------------------------------------------------------------------------------------
do
    local proto_pcm = Proto("pcma", "PCMA")
    
    local fp_payload = ProtoField.bytes("pcma.payload", "Raw")
    
    proto_pcm.fields = {
        fp_payload
    }

    -- Wireshark对每个相关数据包调用该函数
    -- tvb:Testy Virtual Buffer报文缓存; pinfo:packet infomarmation报文信息; treeitem:解析树节点
    function proto_pcm.dissector(tvb, pinfo, tree)
        -- add proto item to tree
        local proto_tree = tree:add(proto_pcm, tvb())
        proto_tree:append_text(string.format(" (Len: %d)",tvb:len()))
        pinfo.columns.protocol = "PCMA"
    end

    -- register this dissector to specific payload type (specified in preferences windows)
    local payload_type_table = DissectorTable.get("rtp.pt")
    function proto_pcm.init()
        payload_type_table:add(8, proto_pcm)
    end

    -- 导出数据到文件部分
    -- for geting data (the field's value is type of ByteArray)
    local f_data = Field.new("pcma")

    local filter_string = nil

    -- menu action. When you click "Tools" will run this function
    local function export_data_to_file()
        -- window for showing information
        local tw = TextWindow.new("Export File Info Win")
        
        -- add message to information window
        function twappend(str)
            tw:append(str)
            tw:append("\n")
        end
        
        -- variable for storing rtp stream and dumping parameters
        local stream_infos = nil

        -- trigered by all ps packats
        local list_filter = ''
        if filter_string == nil or filter_string == '' then
            list_filter = "pcma"
        elseif string.find(filter_string,"pcma")~=nil then
            list_filter = filter_string
        else
            list_filter = "pcma && "..filter_string
        end
        twappend("Listener filter: " .. list_filter .. "\n")
        local my_tap = Listener.new("frame", list_filter)
        
        -- get rtp stream info by src and dst address
        function get_stream_info(pinfo)
            local key = "from_" .. tostring(pinfo.src) .. "_" .. tostring(pinfo.src_port) .. "_to_" .. tostring(pinfo.dst) .. "_" .. tostring(pinfo.dst_port)
            key = key:gsub(":", ".")
            local stream_info = stream_infos[key]
            if not stream_info then -- if not exists, create one
                stream_info = { }
                stream_info.filename = key.. ".pcma.raw"
                stream_info.file = io.open(stream_info.filename, "wb")
                stream_infos[key] = stream_info
                twappend("Ready to export data (RTP from " .. tostring(pinfo.src) .. ":" .. tostring(pinfo.src_port) 
                         .. " to " .. tostring(pinfo.dst) .. ":" .. tostring(pinfo.dst_port) .. " write to file:[" .. stream_info.filename .. "] ...\n")
            end
            return stream_info
        end
        
        -- write data to file.
        local function write_to_file(stream_info, data_bytes)
            stream_info.file:write(data_bytes:raw())
        end
        
        -- call this function if a packet contains ps payload
        function my_tap.packet(pinfo,tvb)
            if stream_infos == nil then
                -- not triggered by button event, so do nothing.
                return
            end
            local datas = { f_data() } -- using table because one packet may contains more than one RTP
            
            for i,data_f in ipairs(datas) do
                if data_f.len < 1 then
                    return
                end
                local data = data_f.range:bytes()
                local stream_info = get_stream_info(pinfo)
                write_to_file(stream_info, data)
            end
        end
        
        -- close all open files
        local function close_all_files()
            if stream_infos then
                local no_streams = true
                for id,stream in pairs(stream_infos) do
                    if stream and stream.file then
                        stream.file:flush()
                        stream.file:close()
                        stream.file = nil
                        twappend("File [" .. stream.filename .. "] generated OK!\n")
                        twappend("ffplay -ar 8000 -ac 1 -f s16le -acodec pcm_alaw -autoexit "..stream.filename)
                        no_streams = false
                    end
                end
                
                if no_streams then
                    twappend("Not found any Data over RTP streams!")
                end
            end
        end
        
        function my_tap.reset()
            -- do nothing now
        end
        
        tw:set_atclose(function ()
            my_tap:remove()
            local tmp = persconffile_path('tmp')
            if Dir.exists(tmp) then
                Dir.remove_all(tmp)
            end
        end)
        
        local function export_data()
            stream_infos = {}
            retap_packets()
            close_all_files()
            stream_infos = nil
        end
        
        tw:add_button("Export All", function ()
            export_data()
        end)

        tw:add_button("Set Filter", function ()
            tw:close()
            dialog_menu()
        end)
    end

    local function dialog_func(str)
        filter_string = str
        export_data_to_file()
    end

    function dialog_menu()
        new_dialog("Filter Dialog",dialog_func,"Filter")
    end

    local function dialog_default()
        filter_string = get_filter()
        export_data_to_file()
    end
    
    -- Find this feature in menu "Tools"
    register_menu("Audio/Export PCMA", dialog_default, MENU_TOOLS_UNSORTED)
end
