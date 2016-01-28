require 'test_helper'

class AttributeMeasuresControllerTest < ActionController::TestCase
  setup do
    @attribute_measure = attribute_measures(:one)
  end

  test "should get index" do
    get :index
    assert_response :success
    assert_not_nil assigns(:attribute_measures)
  end

  test "should create attribute_measure" do
    assert_difference('AttributeMeasure.count') do
      post :create, attribute_measure: { attribute_id: @attribute_measure.attribute_id, value: @attribute_measure.value }
    end

    assert_response 201
  end

  test "should show attribute_measure" do
    get :show, id: @attribute_measure
    assert_response :success
  end

  test "should update attribute_measure" do
    put :update, id: @attribute_measure, attribute_measure: { attribute_id: @attribute_measure.attribute_id, value: @attribute_measure.value }
    assert_response 204
  end

  test "should destroy attribute_measure" do
    assert_difference('AttributeMeasure.count', -1) do
      delete :destroy, id: @attribute_measure
    end

    assert_response 204
  end
end
