def rot47(s):
    out = []
    for c in s:
        o = ord(c)
        if 33 <= o <= 126:
            out.append(chr(33 + ((o + 14) % 94)))
        else:
            out.append(c)
    return ''.join(out)

print(rot47("sggkh://ddd.blfgfyv.xln/dzgxs?e=lzeNgFDWYGN&orhg=IWlzeNgFDWYGN&hgzig_izwrl=1"))
