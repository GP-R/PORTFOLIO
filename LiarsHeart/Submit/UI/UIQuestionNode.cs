using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Events;
using TMPro;

public abstract class UIQuestionNode : MonoBehaviour
{
    [SerializeField] private QuestionNodeSO questionNodeSO;
    public QuestionNodeSO QuestionNodeSO { get => questionNodeSO; }
    
    [SerializeField] private int lineOrder = -1; // 이전 노드 ID값(없을때는 -1)

    private TMP_Text idText;
    private TMP_Text descriptionText;
    private Image lineImage;
    private UIQuestionNode lineNode;

    public event UnityAction<bool> OnCompleteQuestion;

    private bool isCompleteQuestion = false;
    public bool IsCompleteQuestion { get => isCompleteQuestion; }

    protected virtual void Start()
    {
        Init();

        Transform lineTransform = transform.Find("Img_Line");
        if (lineTransform != null)
        {
            lineImage = lineTransform.GetComponent<Image>();
            if (lineImage != null && lineNode != null)
            {
                lineImage.gameObject.SetActive(true);

                float xPos = GetComponent<RectTransform>().anchoredPosition.x - lineNode.GetComponent<RectTransform>().anchoredPosition.x;
                float yPos = GetComponent<RectTransform>().anchoredPosition.y - lineNode.GetComponent<RectTransform>().anchoredPosition.y;
                lineImage.rectTransform.sizeDelta = new Vector2(Mathf.Sqrt((xPos * xPos) + (yPos * yPos)) * 2.0f , 5);
                float thetaDegrees = Mathf.Atan2(yPos, xPos) * Mathf.Rad2Deg + 180;
                lineImage.rectTransform.rotation = Quaternion.Euler(0, 0, thetaDegrees);
            }
        }
    }

    private void Init()
    {
        Transform textId = transform.Find("Text_Id");
        if (textId != null)
        {
            idText = textId.GetComponent<TMP_Text>();
            if(idText != null && questionNodeSO != null)
            {
                idText.text = string.Format("{0:D2}", questionNodeSO.Id);
            }
        }

        Transform textDescription = transform.Find("Text_Description");
        if (textDescription != null )
        {
            descriptionText = textDescription.GetComponent<TMP_Text>();
            if(descriptionText != null && questionNodeSO != null)
            {
                descriptionText.text = questionNodeSO.Description;
            }
        }

        UIQuestionNode[] nodes = this.gameObject.transform.parent.GetComponentsInChildren<UIQuestionNode>(false);
        foreach (UIQuestionNode node in nodes)
        {
            if(node.questionNodeSO != null)
            {
                if(node.questionNodeSO.Id == lineOrder)
                {
                    lineNode = node;
                }
            }
        }
    }

    public void SetQuestionComplete(bool value)
    {
        OnCompleteQuestion.Invoke(value);
    }

    public int GetId()
    {
        if(questionNodeSO != null)
        {
            return questionNodeSO.Id;
        }
        return -1;
    }

    protected virtual void OnDrawGizmos()
    {
        Init();
        if (lineOrder != -1)
        {
            Gizmos.color = Color.red;
            if(lineNode != null)
            {
                Gizmos.DrawLine(transform.position, lineNode.transform.position);
            }
        }
    }

}
