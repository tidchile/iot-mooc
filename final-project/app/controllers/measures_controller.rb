class MeasuresController < ApplicationController
  before_action :set_measure, only: [:show, :update, :destroy]

  # GET /measures
  # GET /measures.json
  def index
    @measures = Measure.all

    render json: @measures
  end

  # GET /measures/1
  # GET /measures/1.json
  def show
    render json: @measure
  end

  # POST /measures
  # POST /measures.json
  def create
    @measure = Measure.new(measure_params)

    if @measure.save
      render json: @measure, status: :created, location: @measure
    else
      render json: @measure.errors, status: :unprocessable_entity
    end
  end

  # PATCH/PUT /measures/1
  # PATCH/PUT /measures/1.json
  def update
    @measure = Measure.find(params[:id])

    if @measure.update(measure_params)
      head :no_content
    else
      render json: @measure.errors, status: :unprocessable_entity
    end
  end

  # DELETE /measures/1
  # DELETE /measures/1.json
  def destroy
    @measure.destroy

    head :no_content
  end

  private

    def set_measure
      @measure = Measure.find(params[:id])
    end

    def measure_params
      params.require(:measure).permit(:attribute_id, :value)
    end
end
