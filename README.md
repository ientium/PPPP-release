# Spell Extraction Guide:

1. Run the modified core.
2. Open the newly created spells.sql with Notepad++ or another text editor and replace all occurances of "^" with "\r", "{" with "\n" and "}" with "\'". This is not mandatory, but recommended if you want decsriptions of spells to be correct. These symbols are replaced during extraction because they break the SQL format. Make sure Search Mode in Notepad++ is set to Normal, or it will replace them with actual new lines. The substitute symbols ^, {, and } were chosen because they do not exist anywhere in the file under normal circumstances, the spell names and descriptions do not contain these 3 symbols.
3. Import spells.sql to your world database.

Tip: If you are not a masochist you will skip this and just download the full world db from brotalnia\database instead.
