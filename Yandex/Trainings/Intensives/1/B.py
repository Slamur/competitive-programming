path = input()

parts = path.split("/")

ans = [""]
for part in parts:
    if "" == part:
        continue
    if "." == part:
        continue
    if ".." == part:
        if len(ans) > 1:
            ans.pop()
        continue
    ans.append(part)

if len(ans) == 1:
    ans.append("")

ans_path = "/".join(ans)
print(ans_path)
