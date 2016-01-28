require 'test_helper'

class AttributesControllerTest < ActionController::TestCase
  setup do
    @attribute = attributes(:one)
  end

  test "should get index" do
    get :index
    assert_response :success
    assert_not_nil assigns(:attributes)
  end

  test "should create attribute" do
    assert_difference('Attribute.count') do
      post :create, attribute: { entity_id: @attribute.entity_id, name: @attribute.name }
    end

    assert_response 201
  end

  test "should show attribute" do
    get :show, id: @attribute
    assert_response :success
  end

  test "should update attribute" do
    put :update, id: @attribute, attribute: { entity_id: @attribute.entity_id, name: @attribute.name }
    assert_response 204
  end

  test "should destroy attribute" do
    assert_difference('Attribute.count', -1) do
      delete :destroy, id: @attribute
    end

    assert_response 204
  end
end
