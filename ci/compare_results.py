import json

with open("./gh-pages/results.json", 'r') as f:
    results = json.load(f)   

for name, tests in results.items():
    print(f"# {name}")
    print("<details>")
    print("<summary>Table</summary>")
    print("")
    print("Test Name | Current, ns | Prev, ns | Ratio")
    print("--- | --- | --- | ---")
    for test_name, data in tests.items():
        new_value = f"{data[-1]['val']}ns"
        old_value = f"{data[-2]['val']}ns" if len(data)> 1 else '.'
        ratio     = float(data[-1]['val'])/float(data[-2]['val']) if len(data)> 1 else '.'
        print(f"{test_name} | { new_value:.2f } | { old_value:.2f } | {ratio:.2f}")
    print("")
    print("</details>")
    print("")
