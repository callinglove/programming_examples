-- Decode param=value from query string of http request uri (http.request.uri)
-- Author: Huang Qiangxiong (qiangxiong.huang@gmail.com)
-- change log:
--      2010-07-01
--          Just can play.
------------------------------------------------------------------------------------------------
do
    local querystring_decoder_proto = Proto("my_http_querystring_decoder", 
                                            "Decoded HTTP URI Query String [HQX's plugins]")

    ---- url decode (from www.lua.org guide)
    function unescape (s)
        s = string.gsub(s, "+", " ")
        s = string.gsub(s, "%%(%x%x)", function (h)
            return string.char(tonumber(h, 16))
        end)
        return s
    end
    
    ---- convert string to hex string
    function string2hex (s)
        local hex = "";
        for i=1, #s, 1 do
            hex = hex .. string.format("%x", s:byte(i))
        end
        return hex
    end
    
    local f_http_uri = Field.new("http.request.uri")

    ---- my dissector
    function querystring_decoder_proto.dissector(tvb, pinfo, tree)
        local http_uri = f_http_uri()
        -- ignore packages without "http.request.uri"
        if not http_uri then return end
        
        -- begin build my tree
        local content = http_uri.value
        local idx = content:find("?")
        if not idx then return end -- not include query string, so stop parsing
        
        local tab = ByteArray.new(string2hex(content)):tvb("Decoded HTTP URI Query String")
        local tab_range = tab()
        
        -- add proto item to tree
        local subtree = tree:add(querystring_decoder_proto, tab_range)
        
        -- add raw data to tree
        subtree:add(tab_range, "[HTTP Request URI] (" .. tab_range:len() .. " bytes)"):add(tab_range, content)

        -- add param value pair to tree
        local pairs_tree = subtree:add(tab_range, "[Decoded Query String]")
        local si = 1
        local ei = idx
        local count = 0
        while ei do
            si = ei + 1
            ei = string.find(content, "&", si)
            local xlen = (ei and (ei - si)) or (content:len() - si + 1)
            if xlen > 0 then
                pairs_tree:add(tab(si-1, xlen), unescape(content:sub(si, si+xlen-1)))
                count = count + 1
            end
        end
        pairs_tree:append_text(" (" .. count .. ")")
        
    end

    -- register this dissector
    register_postdissector(querystring_decoder_proto)
end