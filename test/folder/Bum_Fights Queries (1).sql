use bum_fights;
go

--WHERE clause to see all enemy with attack over 80
--Made by William Bergler
SELECT CharacterID, CharacterName, CharacterAttack
FROM CHARACTER
WHERE CharacterAttack > 80 AND CharacterType = 'Enemy';

--Joining Character to Skill using the Skill Character link table
--Displays character name and the skill they have
--Made by William Bergler
SELECT c.CharacterName, s.SkillName
FROM CHARACTER c JOIN SKILL_CHARACTER sc 
ON c.CharacterID = sc.CharacterID
JOIN SKILL s 
ON sc.SkillID = s.SkillID;

--Uses UNION to show a list of all Items, and Skills
--Orders them in name order and shows if skill or item
--Made by William Bergler
SELECT ItemName AS Name, 'Item' AS Type
FROM ITEM
UNION
SELECT SkillName AS Name, 'Skill' AS Type
FROM SKILL
order by name;

--Displays character names, and their attacks, only displaying when over average attack
--Made by william Bergler
SELECT CharacterID, CharacterName, CharacterAttack, (select avg(CharacterAttack) from character) as [Attack AVG]
FROM CHARACTER
WHERE CharacterAttack > (SELECT AVG(CharacterAttack) FROM CHARACTER);

--Groups characters by their type and displays the ones with more than 3
--Created by William Bergler
SELECT CharacterType, COUNT(CharacterID) AS CharacterCount
FROM CHARACTER
GROUP BY CharacterType
HAVING COUNT(CharacterID) >= 3;
