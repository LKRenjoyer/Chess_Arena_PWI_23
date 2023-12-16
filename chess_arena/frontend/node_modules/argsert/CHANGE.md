# Change Log

List of changes in descending order.

### 08.08.2018 (v1.0.5-v1.0.8)

<table>
  <tr><td>.normalize()</td><td>Fix issue where loop ocurred on rest param args.</td></tr>
  <tr><td>.parseMap()</td><td>Allow "null" to be valid type when not in strict mode.</td></tr>
  <tr><td>map</td><td>Allow using &lt;string...&gt; to denote rest param args.</td></tr>
  <tr><td>.assert()</td><td>Add arg allowing the method name to be displayed in hints.</td></tr>
  <tr><td>options.templates</td><td>Fix bug in templates where format didn't display properly.</td></tr>
</table>

### 07.16.2018 (v1.0.3-v1.0.4)

<table>
  <tr><td>README.md</td><td>Readme falsely noted ".validate()" as method instead of .assert().</td></tr>
  <tr><td>.assert()</td><td>allow passing validator name or func to run on only that validator.</td></tr>
  <tr><td>assertion map</td><td>can now do [username:string] so error messages show named argument see README.md.</td></tr>
</table>