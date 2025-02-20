using UnityEngine;
using UnityEngine.SceneManagement;
using System.Collections.Generic;

public class SubmitManager
{
    public SubmitSO SubmitSO { get; set; }

    private List<UIQuestionNode> questionNodes = new List<UIQuestionNode>();
    private Dictionary<int, string> textNodes = new Dictionary<int, string>();
    private Dictionary<int, List<int>> toggleNodes = new Dictionary<int, List<int>>();
    
    public void SaveNodeData(UIQuestionNode questionNode)
    {
        if (questionNode != null)
        {
            UISelectQuestion selectQuestion = questionNode as UISelectQuestion;
            if(selectQuestion != null)
            {
                toggleNodes.Add(selectQuestion.QuestionNodeSO.Id, selectQuestion.GetQuestionResult());
            }
            UIInputQuestion inputQuestion = questionNode as UIInputQuestion;
            if(inputQuestion != null)
            {
                textNodes.Add(inputQuestion.QuestionNodeSO.Id, inputQuestion.GetQuestionResult());
            }

            questionNodes.Add(questionNode);
        }
    }

    public List<int> GetToggleNodeData(int id)
    {
        List<int> temp = new List<int>();
        if(toggleNodes.TryGetValue(id, out temp))
        {
            return temp;
        }
        return null;
    }

    public string GetTextNodeData(int id)
    {
        string temp = "";
        if(textNodes.TryGetValue(id, out temp))
        {
            return temp;
        }
        return null;
    }

    public void ClearNodes()
    {
        questionNodes.Clear();
        textNodes.Clear();
        toggleNodes.Clear();
    }
}
