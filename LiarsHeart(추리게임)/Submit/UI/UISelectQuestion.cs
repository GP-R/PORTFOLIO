using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UISelectQuestion : UIQuestionNode
{
    [SerializeField] private bool canMultipleSelect = false;

    [SerializeField] private List<UIQuestionToggle> questionToggles = new List<UIQuestionToggle>();
    public List<UIQuestionToggle> QuestionToggles { get => questionToggles; }

    private ToggleGroup toggleGroup = default;

    protected override void Start()
    {
        base.Start();
        toggleGroup = GetComponentInChildren<ToggleGroup>();

        foreach (UIQuestionToggle questionToggle in questionToggles)
        {
            if(questionToggle.GetComponent<Toggle>().isOn)
            {
                SetQuestionComplete(true);
            }
            questionToggle.GetComponent<Toggle>().onValueChanged.AddListener((value) => SetQuestionComplete(value));
        }

        if (!canMultipleSelect)
        {
            foreach (UIQuestionToggle questionToggle in questionToggles)
            {
                questionToggle.GetComponent<Toggle>().group = toggleGroup;
            }
        }
    }

    //선택한 번호 리턴
    public List<int> GetQuestionResult()
    {
        List<int> result = new List<int>();
        foreach(UIQuestionToggle questionToggle in questionToggles)
        {
            Toggle toggle = questionToggle.GetComponent<Toggle>();
            if(toggle != null && toggle.isOn)
            {
                result.Add(questionToggle.Number);
            }
        }
        return result;
    }
}
